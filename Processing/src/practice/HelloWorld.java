package practice;
import processing.core.*;

public class HelloWorld extends PApplet {
	 @Override
	public void setup() {
		size(1920,1080);
		background(0);
	}
	 @Override
	public void draw() {
		int j;
		for(int i = 0; i<=50;i++) {
			j = (int) Math.sqrt(2500-i^2);
			point(i,j);
		}
	}

}
