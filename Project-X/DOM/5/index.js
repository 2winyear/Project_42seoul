// 폼 전송
class User_form {
  constructor(form_name, form_id, form_pwd, form_tel, form_email) {
    this.form_name = form_name;
    this.form_id = form_id;
    this.form_pwd = form_pwd;
    this.form_tel = form_tel;
    this.form_email = form_email;
  }
}
// 빈 배열 생성후 배열 값 push
var obj_array = new Array();

var form_name = document.getElementById("form_name");
var form_id = document.getElementById("form_id");
var form_pwd = document.getElementById("form_pwd");
var form_tel = document.getElementById("form_tel");
var form_email = document.getElementById("form_email");

function form_print() {
  alert('전송');
  obj_array.push(new User_form(document.getElementById("form_name").value,
                document.getElementById("form_id").value,
                document.getElementById("form_pwd").value,
                document.getElementById("form_tel").value,
                document.getElementById("form_email").value));
  console.log(obj_array);

  for(var i = 0; i < obj_array.length; i++) {
    console.log(obj_array[i]);
  }
}

// 메뉴 링크 활성 / 비활성
var on = 1;
function link_switch() {
  if(on == 1)
  {
    document.querySelector(".on_off_google").removeAttribute('href');
    document.querySelector(".on_off_naver").removeAttribute('href');
    document.querySelector(".on_off_apple").removeAttribute('href');
    on = 0;
    console.log("비활성");
  }
  else if(on == 0)
  {
    document.querySelector(".on_off_google").setAttribute('href', "https://google.com");
    document.querySelector(".on_off_naver").setAttribute('href', "https://naver.com");
    document.querySelector(".on_off_apple").setAttribute('href', "https://apple.com");
    on = 1;
    console.log("활성");
  }
}

// 클릭 카운트
var count = 0;
var Count = document.getElementById("count_click");
Count.innerText = `0`;

function count_click() {
  count++;
  console.log(count);
  Count.innerText = `${count}`;
}

// 시간 출력
var Clock = document.getElementById("clock");
function clock() {
    var time = new Date();

    var year = time.getFullYear();
    var month = time.getMonth();
    var date = time.getDate();
    var hours = time.getHours();
    var minutes = time.getMinutes();
    var seconds = time.getSeconds();

    Clock.innerText = 
    `${year}년 ${month + 1}월 ${date}일 ${hours}시 ${minutes}분 ${seconds}초`;
}
clock();
setInterval(clock, 1000); 