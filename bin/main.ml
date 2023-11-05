open Ppx_yojson_conv_lib.Yojson_conv.Primitives

type request_object = { message : string }
[@@deriving yojson] [@@yojson.allow_extra_fields]

let clients : (string, Dream.websocket) Hashtbl.t = Hashtbl.create 5
let forget client_id = Hashtbl.remove clients client_id
let messages = ref []
let add_message message = messages := message :: !messages
let get_messages () = List.rev !messages

let send message =
  Hashtbl.to_seq_values clients
  |> List.of_seq
  |> Lwt_list.iter_p (fun client -> Dream.send client message)

let format_message username message =
  Format.asprintf "[%s]: %s" username message

let handle_client ~username client =
  Hashtbl.replace clients username client;
  let rec loop () =
    match%lwt Dream.receive client with
    | Some body ->
        let ro = body |> Yojson.Safe.from_string |> request_object_of_yojson in
        add_message (format_message username ro.message);
        let content =
          Template.Messages.to_string ~oob:true
            [ format_message username ro.message ]
        in
        let content = content ^ Template.Form.to_string () in
        let%lwt () = send content in
        loop ()
    | None ->
        forget username;
        Dream.close_websocket client
  in
  loop ()

let handle_websocket request =
  match Dream.session_field request "username" with
  | Some username -> Dream.websocket (handle_client ~username)
  | None -> Dream.empty `Bad_Request

let handle_main request =
  match Dream.session_field request "username" with
  | None -> Dream.html @@ Template.Login.to_string request
  | Some _ -> Dream.html @@ Template.Chat.to_string @@ get_messages ()

let handle_session request =
  match%lwt Dream.form request with
  | `Ok body -> (
      match List.assoc_opt "username" body with
      | Some username ->
          let%lwt () = Dream.invalidate_session request in
          let%lwt () = Dream.set_session_field request "username" username in
          Dream.html @@ Template.Chat.to_string @@ get_messages ()
      | None -> Dream.empty `Bad_Request)
  | _ -> Dream.empty `Bad_Request

let () =
  Dream.run @@ Dream.logger @@ Dream.memory_sessions
  @@ Dream.router
       [
         Dream.get "/static/**" (Dream.static "static");
         Dream.get "/" handle_main;
         Dream.post "/session" handle_session;
         Dream.get "/websocket" handle_websocket;
       ]
