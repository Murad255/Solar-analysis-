#pragma once
#include <Arduino.h>
// "<!DOCTYPE html><html><head><link rel="shortcut icon" href="data:image/x-icon;," type="image/x-icon"><meta name="viewport" content="width=device-width, initial-scale=1"><meta http-equiv="Content-Type" content="text/html; charset=utf-8"><title>Умный дом</title>
// <style>
// .bg {background: #000;position: relative; width: 700px;margin: 0 auto;height: 413px;}
// .center {position: relative; width: 700px; margin: 0 auto; height: 70px;}
// .header {width: 100%;height: 72px;background-image: url('https://assets3.insales.ru/assets/1/854/828246/v_1498391792/build/logo.png');background-repeat: no-repeat;}
// .status {width: 100%; height: 50px; font-size: 25px; line-height: 50px; font-family: "Trebuchet MS", Helvetica, sans-serif}
// .ico {width: 40px; height: 40px; top: 30px; background-size:40px;}
// .abs {position: absolute;} #light { background-color: #FF0; width: 100%; height: 100%;} a { text-decoration: none; }
// .button {
// 	float: right;margin: 20px;width: 200px;height: 60px;border: solid 5px #F1F1F1; border-radius: 30px; background-color: #CFD0D0;line-height: 40px;font-size: 25px;text-align: center;
// }
// </style>
// <script>
// var light;
// var button;
// var on = true;
// window.onload = function () {
// 	light = document.getElementById('light');
// 	button = document.getElementById('button');
// 	light.style.visibility = "hidden";
// }
// var send = function(){
// 	console.log('send');
// 	var xhr = new XMLHttpRequest();
// 	console.log(on);
// 	if (on === true) {
// 		button.innerHTML = 'Выключить';
// 		light.style.visibility = "visible";
// 		xhr.open('GET', 'turnOn', false);
// 	} else {
// 		button.innerHTML = 'Включить';
// 		light.style.visibility = "hidden";
// 		xhr.open('GET', 'turnOff', false);
// 	}
// 	on = !on;
// 	xhr.send();
// }
// var send2 = function(){
// 	console.log('send');
// 	var xhr = new XMLHttpRequest();
// 	console.log(on);
// 	if (on === true) {
// 		button.innerHTML = 'Выключить';
// 		light.style.visibility = "visible";
// 		xhr.open('GET', 'ledOn', false);
// 	} else {
// 		button.innerHTML = 'Включить';
// 		light.style.visibility = "hidden";
// 		xhr.open('GET', 'ledOff', false);
// 	}
// 	on = !on;
// 	xhr.send();
// }
// </script>
// </head>
// <body style="font-family:'Trebuchet MS', Helvetica, sans-serif;">
// 	<div style="position: relative; width: 700px; margin: 0 auto;"><a href="http://amperka.ru?utm_source=smart&utm_campaign=iot&utm_medium=wiki"><div style="width: 100%;height: 72px;background-image: url('https://assets3.insales.ru/assets/1/854/828246/v_1498391792/build/logo.png');background-repeat: no-repeat;">&nbsp;</div></a><div style="width:100%;height:50px;font-size:25px;line-height:50px;">№4 Умный дом</div></div>
// 	<div class="bg">
// 		<div class="abs" id="light">&nbsp;</div>
// 		<img class="abs" src="data:image/png;base64,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" />
// 	</div>
// 	<div style="position: relative; width: 700px; margin: 0 auto; height: 70px;">
// 		<a href="https://vk.com/share.php?title=Теперь%20я%20умею%20включать%20дома%20свет%20с%20телефона&image=http://wiki.amperka.ru/_media/iot:city_banner.jpg&url=http%3A//amperka.ru/product/yodo-iot%3Futm_source%3Dsmart%26utm_campaign%3Diot%26utm_medium%3Dvkontakte" target="_blank"><div class="abs ico" style="background-image: url('http://wiki.amperka.ru/_media/iot:vk.png')">&nbsp;</div></a>
// 		<a target="_blank" href="https://www.facebook.com/sharer/sharer.php?u=http%3A%2F%2Famperka.ru%2Fproduct/yodo-iot%3Futm_source%3Dsmart%26utm_campaign%3Diot%26utm_medium%3Dfacebook"><div class="abs ico" style="left:50px; background-image: url('http://wiki.amperka.ru/_media/iot:fb.png')">&nbsp;</div></a>
// 		<button class="button" onclick="send()" id="button">Включить</button>
// 		<button class="button" onclick="send2()" id="button">Включить 2</button>

// 	</div>
// </body>
// </html>"

const String passwordImputPage1 = "<form class=\"form-horizontal\">\
	<fieldset>\
	<!-- Form Name -->\
	<legend>Введите параметры сети и устройства</legend>\
	<!-- Text input-->\
	<div class=\"form-group\">\
	  <label class=\"col-md-4 control-label\" for=\"textinput\">SSID (имя) вашего WI-FI</label>  \
	  <div class=\"col-md-4\">\
	  <input id=\"textinput\" name=\"textinput\" type=\"text\" placeholder=\" \" class=\"form-control input-md\">\
	  <span class=\"help-block\"> </span>  \
	  </div>\
	</div>\
	<!-- Password input-->\
	<div class=\"form-group\">\
	  <label class=\"col-md-4 control-label\" for=\"passwordinput\">Пароль вашего WI-FI</label>\
	  <div class=\"col-md-4\">\
		<input id=\"passwordinput\" name=\"passwordinput\" type=\"password\" placeholder=\" \" class=\"form-control input-md\">\
		<span class=\"help-block\"> </span>\
	  </div>\
	</div>\
	<!-- Text input-->\
	<div class=\"form-group\">\
	  <label class=\"col-md-4 control-label\" for=\"textinput\">Имя устройства</label>  \
	  <div class=\"col-md-4\">\
	  <input id=\"textinput\" name=\"textinput\" type=\"text\" placeholder=\" \" class=\"form-control input-md\">\
	  <span class=\"help-block\"> </span>  \
	  </div>\
	</div>\
	<!-- Text input-->\
	<div class=\"form-group\">\
	  <label class=\"col-md-4 control-label\" for=\"textinput\">Имя рабочей группы</label>  \
	  <div class=\"col-md-4\">\
	  <input id=\"textinput\" name=\"textinput\" type=\"text\" placeholder=\" \" class=\"form-control input-md\">\
	  <span class=\"help-block\"> </span>  \
	  </div>\
	</div>\
	<!-- Button -->\
	<div class=\"form-group\">\
	  <label class=\"col-md-4 control-label\" for=\"\"></label>\
	  <div class=\"col-md-4\">\
		<button id=\"\" name=\"\" class=\"btn btn-success\">Сохранить</button>\
	  </div>\
	</div>\
	</fieldset>\
	</form>";

const String passwordImputPage PROGMEM = "\
	<!DOCTYPE html><html><head><link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"><title>Умный дом</title>\
	<style>\
	.bg {background: #000;position: relative; width: 700px;margin: 0 auto;height: 413px;}\
	.center {position: relative; width: 700px; margin: 0 auto; height: 70px;}\
	.header {width: 100%;height: 72px;background-image: url('https://assets3.insales.ru/assets/1/854/828246/v_1498391792/build/logo.png');background-repeat: no-repeat;}\
	.status {width: 100%; height: 50px; font-size: 25px; line-height: 50px; font-family: \"Trebuchet MS\", Helvetica, sans-serif}\
	.ico {width: 40px; height: 40px; top: 30px; background-size:40px;}\
	.abs {position: absolute;} #light { background-color: #FF0; width: 100%; height: 100%;} a { text-decoration: none; }\
	.button {\
		float: right;margin: 20px;width: 200px;height: 60px;border: solid 5px #F1F1F1; border-radius: 30px; background-color: #CFD0D0;line-height: 40px;font-size: 25px;text-align: center;\
	}\
	</style>\
	<script>\
		var ssidInput;\
		var passwordInput;\
		var nameInput;\
		var grropNameInput;\
		var StatusText;\
		var button;\
		var on = true;\
		window.onload = function () {\
			ssidInput = document.getElementById('ssidInput');\
			passwordInput = document.getElementById('passwordInput');\
			nameInput = document.getElementById('nameInput');\
			grropNameInput = document.getElementById('grropNameInput');\
			button = document.getElementById('saveButton');\
			StatusText = document.getElementById('StatusText');\
		}\
		var send = function(){\
			var sentText='';\
			sentText +=  ssidInput.value;\
			sentText +=  '|';\
			sentText +=  passwordInput.value;\
			sentText +=  '|';\
			sentText +=  nameInput.value;\
			sentText +=  '|';\
			sentText +=  grropNameInput.value;\
			console.log('send');\
			console.log(sentText);\
			console.log(ssidInput.value);			\
			console.log(passwordInput.value);\
			console.log(nameInput.value);\
			console.log(grropNameInput.value);\
			var xhr = new XMLHttpRequest();\
			StatusText.innerHTML= 'сохранено';\
			xhr.open('GET', sentText, false);\
			xhr.send();\
		}\
	</script>\
	</head>\
	<body style=\"font-family:'Trebuchet MS', Helvetica, sans-serif;\">\
			<fieldset>\
			<!-- Form Name -->\
			<legend>Imput to WI-FI and module parameters</legend>\
			<!-- ssid input-->\
			<div class=\"form-group\">\
				<label class=\"col-md-4 control-label\" for=\"textinput\">SSID WI-FI</label>  \
				<div class=\"col-md-4\">\
				<input id=\"ssidInput\" name=\"textinput\" type=\"text\" placeholder=\" \" class=\"form-control input-md\"  >\
				<span class=\"help-block\"> </span>  \
				</div>\
			</div>\
			<!-- Password input-->\
			<div class=\"form-group\">\
				<label class=\"col-md-4 control-label\" for=\"passwordinput\">password WI-FI</label>\
				<div class=\"col-md-4\">\
				<input id=\"passwordInput\" name=\"passwordinput\" type=\"password\" placeholder=\" \" class=\"form-control input-md\">\
				<span class=\"help-block\"> </span>\
				</div>\
			</div>\
			<!-- Text input-->\
			<div class=\"form-group\">\
				<label class=\"col-md-4 control-label\" for=\"textinput\">name module</label>  \
				<div class=\"col-md-4\">\
				<input id=\"nameInput\" name=\"textinput\" type=\"text\" placeholder=\" \" class=\"form-control input-md\">\
				<span class=\"help-block\"> </span>  \
				</div>\
			</div>\
			<!-- Text input-->\
			<div class=\"form-group\">\
				<label class=\"col-md-4 control-label\" for=\"textinput\">name workgroup</label>  \
				<div class=\"col-md-4\">\
				<input id=\"grropNameInput\" name=\"textinput\" type=\"text\" placeholder=\" \" class=\"form-control input-md\">\
				<span class=\"help-block\"> </span>  \
				</div>\
			</div>\
			<!-- Button -->\
			<div class=\"form-group\">\
				<label class=\"col-md-4 control-label\" for=\"\"></label>\
				<div class=\"col-md-4\">\
				<button id=\"saveButton\" name=\"\" onclick=\"send()\" >Save</button>\
				</div>\
			</div>\
			<div id=\"StatusText\" style=\"line-height:35px;font-size:15px\"></div>\
			</fieldset>\
	</body>\
</html>";

const String passwordImputPage2 PROGMEM = "\
<!DOCTYPE html><html><head><link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"><title>Умный дом</title>\
	<style>\
	.bg {background: #000;position: relative; width: 700px;margin: 0 auto;height: 413px;}\
	.center {position: relative; width: 700px; margin: 0 auto; height: 70px;}\
	.header {width: 100%;height: 72px;background-image: url('https://assets3.insales.ru/assets/1/854/828246/v_1498391792/build/logo.png');background-repeat: no-repeat;}\
	.status {width: 100%; height: 50px; font-size: 25px; line-height: 50px; font-family: \"Trebuchet MS\", Helvetica, sans-serif}\
	.ico {width: 40px; height: 40px; top: 30px; background-size:40px;}\
	.abs {position: absolute;} #light { background-color: #FF0; width: 100%; height: 100%;} a { text-decoration: none; }\
	.button {\
		float: right;margin: 20px;width: 200px;height: 60px;border: solid 5px #F1F1F1; border-radius: 30px; background-color: #CFD0D0;line-height: 40px;font-size: 25px;text-align: center;\
	}\
	</style>\
	<script>window.onload = function () {}	</script>\
	</head>\
	<body style=\"font-family:'Trebuchet MS', Helvetica, sans-serif;\">\
		<form method='get' action='wifisave'>\
		<fieldset>\
			<!-- Form Name -->\
			<legend>Imput to WI-FI and module parameters</legend>\
			<!-- ssid input-->\
			<div class=\"form-group\">\
				<label class=\"col-md-4 control-label\" for=\"textinput\">SSID WI-FI</label>  \
				<div class=\"col-md-4\">\
				<input  name = \"ssid\" id=\"ssidInput\"  type=\"text\" placeholder=\" \" class=\"form-control input-md\"  >\
				<span class=\"help-block\"> </span>  \
				</div>\
			</div>\
			<!-- Password input-->\
			<div class=\"form-group\">\
				<label class=\"col-md-4 control-label\" for=\"passwordinput\">password WI-FI</label>\
				<div class=\"col-md-4\">\
				<input  name = \"password\" id=\"passwordInput\"  type=\"password\" placeholder=\" \" class=\"form-control input-md\">\
				<span class=\"help-block\"> </span>\
				</div>\
			</div>\
			<!-- Text input-->\
			<div class=\"form-group\">\
				<label class=\"col-md-4 control-label\" for=\"textinput\">name module</label>  \
				<div class=\"col-md-4\">\
				<input  name = \"name\" id=\"nameInput\" type=\"text\" placeholder=\" \" class=\"form-control input-md\">\
				<span class=\"help-block\"> </span>  \
				</div>\
			</div>\
			<!-- Text input-->\
			<div class=\"form-group\">\
				<label class=\"col-md-4 control-label\" for=\"textinput\">name workgroup</label>  \
				<div class=\"col-md-4\">\
				<input name = \"grropName\" id=\"grropNameInput\" type=\"text\" placeholder=\" \" class=\"form-control input-md\">\
				<span class=\"help-block\"> </span>  \
				</div>\
			</div>\
			<!-- Button -->\
			<div class=\"form-group\">\
				<label class=\"col-md-4 control-label\" for=\"\"></label>\
				<div class=\"col-md-4\">\
				<button id=\"saveButton\" name=\"\"  >Save</button>\
				</div>\
			</div>\
			<div id=\"StatusText\" style=\"line-height:35px;font-size:15px\"></div>\
			</fieldset>\
		</form>	\
	</body>\
</html>";

const String passwordImputPageSaved PROGMEM = " \
<!DOCTYPE html><html><head><link rel=\"shortcut icon\" href=\"data:image/x-icon;,\" type=\"image/x-icon\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"><title>Умный дом</title>\
	<script>window.onload = function () {\
		var statusText = document.getElementById('statusText');\
		statusText.value = 'сохранено';\
	}	</script>\
	</head>\
	<body style=\"font-family:'Trebuchet MS', Helvetica, sans-serif;\">\
		<fieldset>\
			<!-- Form Name -->\
			<legend>Imput to WI-FI and module parameters</legend>\
			<!-- ssid input-->\
			<div class=\"form-group\">\
				<label class=\"col-md-4 control-label\"  id=\"statusText\">Saved</label>  \
			</div>\
			</fieldset>\
	</body>\
</html>";