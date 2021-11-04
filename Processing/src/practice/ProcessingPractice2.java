package practice;
import java.util.ArrayList;
import java.util.List;

import processing.core.*;
public class ProcessingPractice2 extends PApplet{
// Û±Íª•∂Ø mousePressed mouseX mouseY
    List<Position> lines = new ArrayList<Position>();
	Position a = new Position(0,0);
    public void settings() {
        size(1080, 1080);
    }
    
    public void setup() {
    	background(255);
    	lines.add(a);
    }
    int step = 50;
    
	
	
    public void draw() {
    	background(255);
    	
    	Position c = new Position(600,600);
    	lines.add(c);
    	
    	for(int i = 0;i<lines.size();i++) {
    		
    		//line(lines.get(i).x,lines.get(i).y,lines.get(i+1).x,lines.get(i+1).y);
    	}
    	line(lines.get(0).x,lines.get(0).y,lines.get(1).x,lines.get(1).y);
    	System.out.println(lines.get(0).x);
    	
    //	if(mousePressed) {
    //		lines.remove(lines.size()-1);
    //	}
    }

    public static void main (String[] args) {
        ProcessingPractice2 pt = new ProcessingPractice2();
        PApplet.runSketch(new String[]{"ProcessingTest"}, pt);
    }
}

