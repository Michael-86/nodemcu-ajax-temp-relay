const char MAIN_page[] PROGMEM = R"=====(
<HTML>
<TITLE>
REMOTE LED ON/OFF CONTROL
</TITLE>
<BODY>
<CENTER>
<FORM method="post" action="/form">
<TABLE>
<TR><TD colspan=2><B>Mickes control and monitoring center.</B></TD></TR>

<TR><TD><div>Tempratur : <span id="tempratur">0</span> C<br></div></TD><TD>Load Status</TD>
<TR><TD><div>Luftfuktighet : <span id="luftfuktighet">0</span> %<br></div></TD>


<div id="demo">
<TR><TD>
<button type="button" onclick="sendData1(1)">LED ON</button>
<button type="button" onclick="sendData1(0)">LED OFF</button><BR>
</TD>
<TD><span id="LEDState1">NA</span></TD></TR>

<TR><TD>
<button type="button" onclick="sendData2(1)">LED ON</button>
<button type="button" onclick="sendData2(0)">LED OFF</button><BR>
</TD>
<TD><span id="LEDState2">NA</span></TD></TR>

<TR><TD>
<button type="button" onclick="sendData3(1)">LED ON</button>
<button type="button" onclick="sendData3(0)">LED OFF</button><BR>
</TD>
<TD><span id="LEDState3">NA</span></TD></TR>

<TR><TD>
<button type="button" onclick="sendData4(1)">LED ON</button>
<button type="button" onclick="sendData4(0)">LED OFF</button><BR>
</TD>
<TD><span id="LEDState4">NA</span></TD></TR>
</div>
<script>

function sendData1(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("LEDState1").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "button1?LEDstate1="+led, true);
  xhttp.send();
}

function sendData2(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("LEDState2").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "button2?LEDstate2="+led, true);
  xhttp.send();
}

function sendData3(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("LEDState3").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "button3?LEDstate3="+led, true);
  xhttp.send();
}

function sendData4(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("LEDState4").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "button4?LEDstate4="+led, true);
  xhttp.send();
}

//------------------------------------------------------------

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData1();
  getData2();
}, 2000); //2000mSeconds update rate
 
function getData1() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("tempratur").innerHTML =
      this.responseText;    
    }
  };
  xhttp.open("GET", "readtemp", true);
  xhttp.send();
}

function getData2() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("luftfuktighet").innerHTML =
      this.responseText;      
    }
  };
  xhttp.open("GET", "readhum", true);
  xhttp.send();
}
</script>

<TR><TD colspan=2><B><CENTER><A href = "/update">Update</a></CENTER></B></TD></TR>
</TABLE>
</FORM>

</CENTER>
</BODY>
</HTML>
)=====";
