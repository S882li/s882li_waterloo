package practice;
import processing.core.*;
public class ProcessingPractice1 extends PApplet{
// Û±Íª•∂Ø mousePressed mouseX mouseY
    @Override
    public void settings() {
        size(1080, 1080);
    }
    
    public void setup() {
    	background(255);
    }
    int step = 50;
    @Override
    public void draw() {
    	background(255);
    	int a = 0;
    	
    	for(a = 1; a <= step; a++) {
    		noFill();
    		ellipse(mouseX/step*a,mouseY/step*a,500,500);
    	}
    	
    	if(mousePressed) {
    		step-=5;
    		if(step<=0) {
    			step = 50;
    		}
    	}
    	
    	line(150, 25, mouseX, mouseY);

    }

    public static void main (String[] args) {
        ProcessingPractice1 pt = new ProcessingPractice1();
        PApplet.runSketch(new String[]{"ProcessingTest"}, pt);
    }
}

