if (!!window.EventSource) {
    var gateway = `ws://${window.location.hostname}/ws`;
    var websocket;
    window.addEventListener('load', onLoad);
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
      var state;
      if (event.data == "1"){
        state = "ON";
      }
      else{
        state = "OFF";
      }
      document.getElementById('state').innerHTML = state;
    }
    function onLoad(event) {
      initWebSocket();
      initButton();
    }
    function initButton() {
      document.getElementById('button').addEventListener('click', toggle);
    }
    function toggle(){
      websocket.send('toggle');
    }
    // var source = new EventSource('/events');
  
    // source.addEventListener('open', function(e) {
    //   console.log("Events Connected"); }, false);
  
    // source.addEventListener('error', function(e) {
    //   if (e.target.readyState != EventSource.OPEN) {
    //     console.log("Events Disconnected");
    //   }
    // }, false);
  
    // source.addEventListener('message', function(e) {
    //   console.log("message", e.data);
    // }, false);
  
    // source.addEventListener('temperature', function(e) {
    //   console.log("temperature", e.data);
    //   document.getElementById("temp").innerHTML = e.data;
    // }, false);
  
    // source.addEventListener('humidity', function(e) {
    //   console.log("humidity", e.data);
    //   document.getElementById("hum").innerHTML = e.data;
    // }, false);
  
    // source.addEventListener('pressure', function(e) {
    //   console.log("pressure", e.data);
    //   document.getElementById("pres").innerHTML = e.data;
    // }, false);
    var chartT = new Highcharts.Chart({
      chart:{ renderTo : 'chart-temperature' },
      title: { text: '' },
      series: [{
        showInLegend: false,
        data: []
      }],
      plotOptions: {
        line: { animation: false,
          dataLabels: { enabled: true }
        },
        series: { color: '#ca0b0b' }
      },
      xAxis: { type: 'datetime',
        dateTimeLabelFormats: { second: '%H:%M:%S' }
      },
      yAxis: {
        title: { text: ' ' }
        //title: { text: 'Temperature (Fahrenheit)' }
      },
      credits: { enabled: false }
    });
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          var x = (new Date()).getTime(),
              y = parseFloat(this.responseText);
          //console.log(this.responseText);
          if(chartT.series[0].data.length > 40) {
            chartT.series[0].addPoint([x, y], true, true, true);
          } else {
            chartT.series[0].addPoint([x, y], true, false, true);
          }
        }
      };
      xhttp.open("GET", "/temperature", true);
      xhttp.send();
    }, 2000 ) ;
    
    var chartH = new Highcharts.Chart({
      chart:{ renderTo:'chart-humidity' },
      title: { text: '' },
      series: [{
        showInLegend: false,
        data: []
      }],
      plotOptions: {
        line: { animation: false,
          dataLabels: { enabled: true }
        },
        series: { color: '#0a18da' }
      },
      xAxis: {
        type: 'datetime',
        dateTimeLabelFormats: { second: '%H:%M:%S' }
      },
      yAxis: {
        title: { text: ' ' }
      },
      credits: { enabled: false }
    });
    setInterval(function ( ) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          var x = (new Date()).getTime(),
              y = parseFloat(this.responseText);
          //console.log(this.responseText);
          if(chartH.series[0].data.length > 40) {
            chartH.series[0].addPoint([x, y], true, true, true);
          } else {
            chartH.series[0].addPoint([x, y], true, false, true);
          }
        }
      };
      xhttp.open("GET", "/humidity", true);
      xhttp.send();
    }, 2000 ) ;
  }