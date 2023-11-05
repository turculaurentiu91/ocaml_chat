open Tyxml;

let html_to_string = html => Format.asprintf("%a", Tyxml.Html.pp_elt(), html);

module Messages = {
  let createElement = (~oob=false, ~messages=[], ()) => {
    let messages = List.map(e => <li> {Html.txt(e)} </li>, messages);
    oob
      ? <ul className="messages" _hx_swap_oob="afterbegin" id="messages">
          ...messages
        </ul>
      : <ul className="messages" id="messages"> ...messages </ul>;
  };

  let to_string = (~oob=false, messages) =>
    createElement(~oob, ~messages, ()) |> html_to_string;
};

module Form = {
  let createElement = () =>
    <form
      _ws_send="true"
      id="form"
      className="form"
      _hx_on="htmx:wsAfterSend: this.reset(); this.querySelector('input').focus()">
      <input _type="text" id="message" name="message" autofocus=() />
      <button type_="submit" className="button">
        <Html.svg
          fill="none"
          viewBox="0 0 24 24"
          stroke_width="1.5"
          stroke="currentColor">
          <path
            stroke_linecap="round"
            stroke_linejoin="round"
            d="M6 12L3.269 3.126A59.768 59.768 0 0121.485 12 59.77 59.77 0 013.27 20.876L5.999 12zm0 0h7.5"
          />
        </Html.svg>
      </button>
    </form>;

  let to_string = () => createElement() |> html_to_string;
};

module Page = {
  let createElement = (~children, ()) =>
    <html>
      <head>
        <meta
          name="viewport"
          content="width=device-width, initial-scale=1.0"
        />
        <title> {Html.txt("OCaml Chat")} </title>
        <script _defer="defer" src="/static/htmx.js" />
        <script _defer="defer" src="/static/htmx-ws.js" />
        <link rel="stylesheet" href="/static/style.css" />
      </head>
      <body
        _hx_on="htmx:oobAfterSwap: document.querySelector('input').scrollIntoView(true)">
        ...children
      </body>
    </html>;
};

module Chat = {
  let createElement = (~messages, ()) =>
    <Page>
      <div className="main-container" _hx_ext="ws" _ws_connect="/websocket">
        <h1 className="title"> {Html.txt("Welcome to ocaml chatroom!")} </h1>
        <Messages messages />
        <Form />
      </div>
    </Page>;

  let to_string = messages => createElement(~messages, ()) |> html_to_string;
};

module Login = {
  let createElement = (~request, ()) =>
    <Page>
      <div className="login-container">
        <h1> {Html.txt("Welcome to ocaml chatroom!")} </h1>
        <p>
          {Html.txt("You need to setup your username to access the chatroom")}
        </p>
        <form _hx_post="/session" _hx_target="body">
          {Html.Unsafe.data(Dream.csrf_tag(request))}
          <div className="input-group">
            <label htmlFor="username"> {Html.txt("User name")} </label>
            <input type_="text" value="" name="username" id="username" />
          </div>
          <button type_="submit" className="button">
            {Html.txt("Login")}
          </button>
        </form>
      </div>
    </Page>;

  let to_string = request => createElement(~request, ()) |> html_to_string;
};
