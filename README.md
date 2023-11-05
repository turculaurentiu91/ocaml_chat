# OCaml Chat

OCaml Chat is a simple chat room application built with [Dream](https://github.com/aantron/dream) and [HTMX](https://htmx.org/). This project serves as a learning venture into OCaml, exploring functional programming principles, web development with Dream, real-time interactivity with HTMX, and WebSocket communication.

## Features

- Real-time messaging between clients using WebSockets.
- User session management for login and chat participation.
- Modular code structure with separate concerns for handling HTTP requests, WebSocket connections, and HTML template rendering.
- Type-safe HTML generation using [Tyxml](https://github.com/ocsigen/tyxml).

## Installation

Ensure you have OCaml and the Dune build system installed on your machine. You can then clone this repository and build the project:

```bash
git clone https://github.com/turculaurentiu91/ocaml_chat.git
cd ocaml_chat
dune build
```

## Usage

Run the server using the following command:

```bash
dune exec bin/main.exe
```

Once the server is running, navigate to http://localhost:8080 in your web browser. You can log in (or create an account) and start chatting!

## Contributing

This project is primarily a learning venture, but contributions, suggestions, and discussions are welcome! Feel free to open issues or submit pull requests.

## License

This project is licensed under the MIT License.

## Acknowledgments

Special thanks to the creators and maintainers of Dream, HTMX, and Tyxml for providing the libraries that made this project possible.
