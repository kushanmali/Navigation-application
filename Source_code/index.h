const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>

<html >
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!------<title> Website Layout | CodingLab</title>------>
    <title> NSBM Walker</title>
  <style type="text/css">
    

    @import url('https://fonts.googleapis.com/css2?family=Poppins:wght@200;300;400;500;600;700&display=swap');
*{
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  font-family: 'Poppins',sans-serif;
}
::selection{
  color: #000;
  background: #fff;
}
nav{
  position: fixed;
  background: #1b1b1b;
  width: 100%%;
  padding: 10px 0;
  z-index: 12;
}
nav .menu{
  max-width: 1250px;
  margin: auto;
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 0 20px;
}
.menu .logo a{
  text-decoration: none;
  color: #fff;
  font-size: 35px;
  font-weight: 600;
}
.menu ul{
  display: inline-flex;
}
.menu ul li{
  list-style: none;
  margin-left: 7px;
}
.menu ul li:first-child{
  margin-left: 0px;
}
.menu ul li a{
  text-decoration: none;
  color: #fff;
  font-size: 18px;
  font-weight: 500;
  padding: 8px 15px;
  border-radius: 5px;
  transition: all 0.3s ease;
}
.menu ul li a:hover{
  background: #fff;
  color: black;
}
.img{
  background: url('https://www.maga.lk/wp-content/uploads/2018/03/DSC_4723.jpg')no-repeat;
  width: 100%%;
  height: 100vh;
  background-size: cover;
  background-position: center;
  position: relative;
}
.img::before{
  content: '';
  position: absolute;
  height: 100%%;
  width: 100%%;
  background: rgba(0, 0, 0, 0.4);
}
.center{
  position: absolute;
  top: 52%%;
  left: 50%%;
  transform: translate(-50%%, -50%%);
  width: 100%%;
  padding: 0 20px;
  text-align: center;
}
.center .title{
  color: #fff;
  font-size: 37px;
  font-weight: 600;
}
.center .sub_title{
  color: #fff;
  font-size: 52px;
  font-weight: 600;
}
.center .btns{
  margin-top: 20px;
}
.center .btns button{
  height: 75px;
  width: 290px;
  border-radius: 5px;
  border: none;
  margin: 0 10px;
  border: 2px solid white;
  font-size: 20px;
  font-weight: 500;
  padding: 0 10px;
  cursor: pointer;
  outline: none;
  transition: all 0.3s ease;
}
.center .btns button:first-child{
  color: #fff;
  background: none;
}
.btns button:first-child:hover{
  background: white;
  color: black;
}
.center .btns button:last-child{
  background: white;
  color: black;
}

  </style>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.2/css/all.min.css"/>
   </head>
<body>
 


  <nav>
    <div class="menu">
      <div class="logo">
        <a href="#">NSBM Walker</a>
      </div>
      <ul>
        <li><a href="#"></a></li>
        
      </ul>
    </div>
  </nav>

  <div class="img"></div>
  <div class="center">
      <br><br>
    <div class="title"> </div>
 <br>
    <br>
          <h2>Click the name of the button according to the location you want to navigate to</h2>
           


    <div class="btns">


       <br>


      <a href="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=6.820244618019134+80.03952972189296"><button >Faculty Of Computing</button></a> 

  <a href="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=6.820594453405693+80.03915669390773"><button >Faculty⁩ of Business</button></a>
      <a href="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=6.821034256518453+80.0390200622326"><button >Faculty of Engineering</button></a>
      <a href="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=6.821022917508989+80.0381238614284"><button >Hostel Complex</button></a>
      <a href="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=6.821052610291951+80.03959019545223"><button >Administration Office</button></a>
      <a href="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=6.820729763732591+80.03950467412825"><button >Library</button></a>
      <a href="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=6.820698150252388+80.04020529485592"><button >Medical Center</button></a> 
      <a href="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=6.820981105805472+80.04083134695742"><button >Auditorium</button></a>
      <a href="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=6.820596634595082+80.0417420289115"><button >Student Car Park</button></a>
      <a href="http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=6.82214935609664, 80.04069384281813"><button >Playground</button></a>
      
      

    </div>
  </div>

</body> 
</html>
)=====";
