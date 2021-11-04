package practice;
import processing.core.*;
public class ProcessingTest extends PApplet{

    @Override
    public void settings() {
        size(1920, 1080);
    }

    @Override
    public void draw() {
    	int a = 0;
    	int b = 0;
    	for(int i = 0; i<100;i++){
    		    if((i%7 ==1)|| (i%7 ==4)|| (i%7 ==2)){
    		      fill(250,250,250);
    		      stroke(250,250,250);
    		      rect(a*40,0,40,1080);
    		            a++;
    		      a++;
    		    }else{
    		      
    		      fill(50,200,50);
    		      stroke(50,200,50);
    		      rect(0,b*40,1920,40);
    		      b+=2;
    		    }
    		  }

    }

    public static void main (String[] args) {
        ProcessingTest pt = new ProcessingTest();
        PApplet.runSketch(new String[]{"ProcessingTest"}, pt);
    }
}

//终于搞定了java用
//一个绿色随机百叶窗效果orz