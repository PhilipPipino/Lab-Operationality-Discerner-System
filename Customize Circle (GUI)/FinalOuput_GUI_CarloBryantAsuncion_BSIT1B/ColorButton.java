package FinalOuput_GUI_CarloBryantAsuncion_BSIT1B;
import java.awt.*;
import java.awt.event.ActionEvent;

public class ColorButton extends Button{
	
	//Auto-generated UID, required in compilation
	private static final long serialVersionUID = -2308136117143403774L;
	//circle object declaration
	private Circle circle;
	
	//ColorButton constructor method
    public ColorButton(String text, Circle circle) {
        super(text);
        this.circle=circle;
    }

    public void actionPerformed(ActionEvent e) {
    	//Integer clicks is increased by one when clicked
    	setClicks(getClicks()+1);
    	
    	//clicks is reverted to one, so that flow
    	//of the color change is consistent
    	if(getClicks()>3) setClicks(1);
    	System.out.print("COLOR BUTTON CLICKED, color changed to ");
    		
    		//if-else statements for the color change
    		if (getClicks()%3==0) { 
    			circle.setColor(Color.BLUE);
    			System.out.println("blue");
    		} else if (getClicks()%2==0) {
    			circle.setColor(Color.GREEN);
    			System.out.println("green");
    		} else { 
    			circle.setColor(Color.RED);
    			System.out.println("red");
    		} circle.repaint();
    }
}