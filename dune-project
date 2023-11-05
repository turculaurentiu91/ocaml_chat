(lang dune 3.11)

(name ocaml_chat)

(generate_opam_files true)

(source
 (github turculaurentiu91/ocaml_chat))

(authors "Turcu Laurentiu")

(maintainers "Turcu Laurentiu")

(license LICENSE)

(documentation https://github.com/turculaurentiu91/ocaml_chat)

(package
 (name ocaml_chat)
 (synopsis "A chat room implemented in ocaml")
 (description "A chat room implemented in ocaml for me to learn OCaml, it uses websockets and HTMx")
 (depends ocaml dune)
 (tags
  (OCaml Dream Websocket HTMx)))

; See the complete stanza docs at https://dune.readthedocs.io/en/stable/dune-files.html#dune-project
