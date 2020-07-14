import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class emmulatorCOproject extends PApplet {

  
BufferedReader reader;
String line;
PImage img,img2;
int counter=0;
String title="EMMULATOR BY SWAYAM, MOULIK And RISHABH";
 int count=1;
 ArrayList<String> s=new ArrayList<String>();
public void setup() {
    
    if(args!=null){
      println(args[0]);
      reader = createReader(args[0]);
      img = loadImage(args[1]);
      img2 = loadImage(args[2]);
    }
    else{
     img = loadImage("arrow.jpeg");
     img2=loadImage("arrowcopy.jpeg");
  reader = createReader("opFile.txt");   
    }
   readline();

}
 
public void draw() {
  background(0);
  textSize(50);
  text(title,50,100);
       textSize(30);
     
  text("Token No:",113,350+50);
 rect(300, 310+50, 70, 55);
 fill(0);
 text(s.get(counter).substring(s.get(counter).indexOf("tokenNo:")+"tokenNo:".length(),s.get(counter).indexOf(", line")),300,350+50);
fill(255);
  image(img,(width/2)+img.width+5-30, 150);
  image(img2,(width/2)-img.width-5-30, 150);
  text("Command: ",302,318);
  rect(484, 287, 400, 60);
  fill(0);
  text(s.get(counter).substring(s.get(counter).indexOf(", line:")+", line:".length(),s.get(counter).indexOf(", A")),489,335);
  fill(255);
  
  
  //A
  text("A: ",131,534);
  rect(170 ,508, 60, 40);
  fill(0);
  text(s.get(counter).substring(s.get(counter).indexOf(", A:")+", A:".length(),s.get(counter).indexOf(", B")),176,541);
  fill(255);
  
  //B
  text("B: ",131+150,534);
 rect(170+150 ,508, 60, 40);
  fill(0);
  text(s.get(counter).substring(s.get(counter).indexOf(", B:")+", B:".length(),s.get(counter).indexOf(", C")),326,538);
  fill(255);
  //C
  text("C: ",131+(2*150),534);
 rect(170+(2*150) ,508, 60, 40);
  fill(0);
  text(s.get(counter).substring(s.get(counter).indexOf(", C:")+", C:".length(),s.get(counter).indexOf(", D")),477,537);
  fill(255);
  //D
  text("D: ",131+(3*150),534);
 rect(170+(3*150) ,508, 60, 40);
  fill(0);
  text(s.get(counter).substring(s.get(counter).indexOf(", D:")+", D:".length(),s.get(counter).indexOf(", MA")),627,537);
  fill(255);
  //MA
  text("MA: ",131+(4*150),534);
 rect(170+(4*150)+20 ,508, 60, 40);
  fill(0);
  text(s.get(counter).substring(s.get(counter).indexOf(", MA:")+", MA:".length(),s.get(counter).indexOf(", MB")),796,539);
  fill(255);
  //MB
  text("MB: ",131+(5*150),534);
 rect(170+(5*150)+20 ,508, 60, 40);
  fill(0);
  text(s.get(counter).substring(s.get(counter).indexOf(", MB:")+", MB:".length(),s.get(counter).indexOf(", SP")),945,542);
  fill(255);
  //SP
  text("SP: ",131+(6*150),534);
 rect(170+(6*150)+20 ,508, 60, 40);
  fill(0);
  text(s.get(counter).substring(s.get(counter).indexOf(", SP:")+", SP:".length(),s.get(counter).indexOf(", SIZE")),1096,540);
  fill(255);
  //Size
  text("Size: ",487,640);
  rect(568,615, 60, 40);
  fill(0);
  text(s.get(counter).substring(s.get(counter).indexOf(", SIZE:")+", SIZE:".length(),s.get(counter).indexOf(", ARRAY")),572,644);
  fill(255);
  //Array
  text("Array: ",325-50,756);
  rect(454-50, 720, 600, 60);
  fill(0);
  text(s.get(counter).substring(s.get(counter).indexOf(", ARRAY:")+", ARRAY:".length(),s.get(counter).indexOf("}*")+1),410,772);
  fill(255);
} 


public void readline(){
  
  while(true){
    try {
    line = reader.readLine();
  } catch (IOException e) {
    e.printStackTrace();
    line = null;
  }
  if (line == null) {
    // Stop reading because of an error or file is empty
  break; 
  } else {
     println(line);
    s.add(line);
   
  }
  }
}


public void mouseClicked() {
println(mouseX,mouseY);
if(mouseX>=521&&mouseX<=606&&mouseY>=152&&mouseY<=184){
  if(counter>0);
  counter--;
  println(counter);
}
else if(mouseX>=701&&mouseX<=785&&mouseY>=153&&mouseY<=226){
  if(counter<s.size()){
    counter++;
     println(counter);
}
}
}
  public void settings() {  size(1280,840); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "emmulatorCOproject" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
