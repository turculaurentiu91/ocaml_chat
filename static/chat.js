let message = document.getElementById("message");
let chat = document.getElementById("messages");
let socket = new WebSocket("ws://" + window.location.host + "/websocket");
let form = document.getElementById("form");

socket.onmessage = function(event) {
  let item = document.createElement("li");
  item.innerText = event.data;
  chat.appendChild(item);
};

form.addEventListener("submit", function(event) {
  event.preventDefault();

  if (socket.readyState != WebSocket.OPEN || !message.value) {
    return false;
  }

  socket.send(message.value);
  message.value = "";
  return false;
});
