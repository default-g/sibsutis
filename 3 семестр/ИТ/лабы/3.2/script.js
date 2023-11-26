function getCookie(name) {
  const value = `; ${document.cookie}`;
  const parts = value.split(`; ${name}=`);
  if (parts.length === 2) return parts.pop().split(";").shift();
}

function registration() {
  if (document.myform.username.value == "") {
    alert("Enter some value!");
    return;
  }
  username = escape(document.myform.username.value) + ";";
  date = new Date();
  document.cookie = "username=" + username;
  document.cookie = "lastvisit=" + date;
  document.cookie = "amountofvisits=" + 0;
  location.reload();
}

function calculateTimeAmount(startTime, endTime) {
  startTime = new Date(startTime);
  endTime = new Date(endTime);
  var timeDiff = endTime - startTime;
  var msec = timeDiff;
  var months = Math.floor(msec / (1000 * 60 * 60 * 24 * 31));
  msec -= months * 1000 * 60 * 60 * 24 * 31;
  var days = Math.floor(msec / (1000 * 60 * 60 * 24));
  msec -= days * 1000 * 60 * 60 * 24;
  var hours = Math.floor(msec / 1000 / 60 / 60);
  msec -= hours * 1000 * 60 * 60;
  var minutes = Math.floor(msec / 1000 / 60);
  msec -= minutes * 1000 * 60;
  var seconds = Math.floor(msec / 1000);
  msec -= seconds * 1000;
  var stringToReturn = "";
  if (months) {
    stringToReturn += months + " месяцев, ";
  }
  if (days) {
    stringToReturn += days + " дней, ";
  }
  if (hours) {
    stringToReturn += hours + " часов, ";
  }
  if (minutes) {
    stringToReturn += minutes + " минут, ";
  }
  if (seconds) {
    stringToReturn += seconds + " секунд";
  }
  return stringToReturn;
}

if (document.cookie) {
  document.getElementById("hascookie").setAttribute("style", "display:unset;");
  document.getElementById("greetings").innerHTML =
    "Привет, " + getCookie("username") + "!";
  var now = new Date();
  var timeDiff = calculateTimeAmount(getCookie("lastvisit"), now);
  document.cookie = "lastvisit=" + now;
  var amountOfVisits = getCookie("amountofvisits");
  amountOfVisits++;
  document.cookie = "amountofvisits=" + amountOfVisits;
  document.getElementById("amountofvisits").innerHTML =
    "Количество посещений " + amountOfVisits;
  if(amountOfVisits >= 5) {
    document.getElementById("amountofvisits").setAttribute("style", "color:red");
  }
  document.getElementById("lastvisit").innerHTML =
    "С последнего посещения прошло: " + timeDiff;
  document
    .getElementById("deletevisits")
    .setAttribute("style", "display:unset;");
}
