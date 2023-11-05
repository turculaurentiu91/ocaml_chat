open Tyxml;

let html_to_string = html => Format.asprintf("%a", Tyxml.Html.pp_elt(), html);

module Messages = {
  let createElement = (~oob=false, ~messages=[], ()) => {
    let messages = List.map(e => <li> {Html.txt(e)} </li>, messages);
    oob
      ? <ul _hx_swap_oob="beforeend" id="messages"> ...messages </ul>
      : <ul id="messages"> ...messages </ul>;
  };

  let to_string = (~oob=false, messages) =>
    createElement(~oob, ~messages, ()) |> html_to_string;
};

module Form = {
  let createElement = () =>
    <form _ws_send="true" id="form">
      <input _type="submit" value="Send" />
      <input _type="text" id="message" name="message" size="64" autofocus=() />
    </form>;

  let to_string = () => createElement() |> html_to_string;
};

module Page = {
  let createElement = (~children, ()) =>
    <html>
      <head>
        <title> {Html.txt("Hello")} </title>
        <script _defer="defer" src="/static/htmx.js" />
        <script _defer="defer" src="/static/htmx-ws.js" />
      </head>
      <body> ...children </body>
    </html>;
};

module Chat = {
  let createElement = (~messages, ()) =>
    <Page>
      <h1 className="hello"> {Html.txt("Welcome to chat!")} </h1>
      <div _hx_ext="ws" _ws_connect="/websocket">
        <Form />
        <Messages messages />
      </div>
    </Page>;

  let to_string = messages => createElement(~messages, ()) |> html_to_string;
};

module Login = {
  let createElement = (~request, ()) =>
    <Page>
      <h1> {Html.txt("Login")} </h1>
      <p>
        {Html.txt(
           "If you don't have an account, this will create one ofr you",
         )}
      </p>
      <form _hx_post="/session" _hx_target="body">
        {Html.Unsafe.data(Dream.csrf_tag(request))}
        <div>
          <label htmlFor="username"> {Html.txt("User name")} </label>
          <input type_="text" value="" name="username" id="username" />
        </div>
        <div>
          <label htmlFor="password"> {Html.txt("Password")} </label>
          <input type_="password" value="" name="password" id="password" />
        </div>
        <button type_="submit"> {Html.txt("Login")} </button>
      </form>
    </Page>;

  let to_string = request => createElement(~request, ()) |> html_to_string;
};
