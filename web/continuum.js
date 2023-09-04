var slider0 = document.getElementById("servoSlider0");
    var servoP0 = document.getElementById("servoPos0");
    servoP0.innerHTML = slider0.value;
    slider0.oninput = function() {
      slider0.value = this.value;
      servoP0.innerHTML = this.value;
    }

var slider1 = document.getElementById("servoSlider1");
    var servoP1 = document.getElementById("servoPos1");
    servoP1.innerHTML = slider1.value;
    slider1.oninput = function() {
      slider1.value = this.value;
      servoP1.innerHTML = this.value;
    }

var slider2 = document.getElementById("servoSlider2");
    var servoP2 = document.getElementById("servoPos2");
    servoP2.innerHTML = slider2.value;
    slider2.oninput = function() {
      slider2.value = this.value;
      servoP2.innerHTML = this.value;
    }

var slider3 = document.getElementById("servoSlider3");
    var servoP3 = document.getElementById("servoPos3");
    servoP3.innerHTML = slider3.value;
    slider3.oninput = function() {
      slider3.value = this.value;
      servoP3.innerHTML = this.value;
    }

var slider4 = document.getElementById("servoSlider4");
    var servoP4 = document.getElementById("servoPos4");
    servoP4.innerHTML = slider4.value;
    slider4.oninput = function() {
      slider4.value = this.value;
      servoP4.innerHTML = this.value;
    }

var slider5 = document.getElementById("servoSlider5");
    var servoP5 = document.getElementById("servoPos5");
    servoP5.innerHTML = slider5.value;
    slider5.oninput = function() {
      slider5.value = this.value;
      servoP5.innerHTML = this.value;
    }

var slider6 = document.getElementById("servoSlider6");
    var servoP6 = document.getElementById("servoPos6");
    servoP6.innerHTML = slider6.value;
    slider6.oninput = function() {
      slider6.value = this.value;
      servoP6.innerHTML = this.value;
    }

var slider7 = document.getElementById("servoSlider7");
    var servoP7 = document.getElementById("servoPos7");
    servoP7.innerHTML = slider7.value;
    slider7.oninput = function() {
      slider7.value = this.value;
      servoP7.innerHTML = this.value;
    }

var slider8 = document.getElementById("servoSlider8");
    var servoP8 = document.getElementById("servoPos8");
    servoP8.innerHTML = slider8.value;
    slider8.oninput = function() {
      slider8.value = this.value;
      servoP8.innerHTML = this.value;
    }

var slider9 = document.getElementById("servoSlider9");
    var servoP9 = document.getElementById("servoPos9");
    servoP9.innerHTML = slider9.value;
    slider9.oninput = function() {
      slider9.value = this.value;
      servoP9.innerHTML = this.value;
    }

var slider10 = document.getElementById("servoSlider10");
    var servoP10 = document.getElementById("servoPos10");
    servoP10.innerHTML = slider10.value;
    slider10.oninput = function() {
      slider10.value = this.value;
      servoP10.innerHTML = this.value;
    }

var slider11 = document.getElementById("servoSlider11");
    var servoP11 = document.getElementById("servoPos11");
    servoP11.innerHTML = slider11.value;
    slider11.oninput = function() {
      slider11.value = this.value;
      servoP11.innerHTML = this.value;
    }

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;
window.addEventListener('load', onLoad);

function onLoad(event) {
  initWebSocket();
}

function initWebSocket() {
  console.log('Trying to open a WebSocket connection...');
  websocket = new WebSocket(gateway);
  websocket.onopen    = onOpen;
  websocket.onclose   = onClose;
  websocket.onmessage = onMessage; // <-- add this line
}
function onOpen(event) {
  console.log('Connection opened');
}
function onClose(event) {
  console.log('Connection closed');
  setTimeout(initWebSocket, 2000);
}
function onMessage(event) {
  document.getElementById("servoPos0").innerHTML = event.data;
  document.getElementById("servoPos1").innerHTML = event.data;
  document.getElementById("servoPos2").innerHTML = event.data;
  document.getElementById("servoPos3").innerHTML = event.data;
  document.getElementById("servoPos4").innerHTML = event.data;
  document.getElementById("servoPos5").innerHTML = event.data;
  document.getElementById("servoPos6").innerHTML = event.data;
  document.getElementById("servoPos7").innerHTML = event.data;
  document.getElementById("servoPos8").innerHTML = event.data;
  document.getElementById("servoPos9").innerHTML = event.data;
  document.getElementById("servoPos10").innerHTML = event.data;
  document.getElementById("servoPos11").innerHTML = event.data;
}

function submitForm(){
  slider0;
  slider1;
  slider2;
  slider3;
  slider4;
  slider5;
  slider6;
  slider7;
  slider8;
  slider9;
  slider10;
  slider11;

  websocket.send(slider0.value+"&"+slider1.value+"&"+slider2.value+"&"
                +slider3.value+"&"+slider4.value+"&"+slider5.value+"&"
                +slider6.value+"&"+slider7.value+"&"+slider8.value+"&"
                +slider9.value+"&"+slider10.value+"&"+slider11.value);
}