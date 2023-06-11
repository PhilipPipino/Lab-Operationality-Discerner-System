package FinalOuput_GUI_CarloBryantAsuncion_BSIT1B;
import java.awt.event.ActionEvent;

class SizeButton extends Button {
	
	//Auto-generated UID, required in compilation
	private static final long serialVersionUID = 6550475728883266530L;
	//circle object declaration
	private Circle circle;
	private int xSize, ySize;
	
	//SizeButton constructor method
    public SizeButton(String text, Circle circle) {
        super(text);
        this.circle = circle;
    }

    public void actionPerformed(ActionEvent e) {
    	//Integer clicks is increased by one when clicked
        setClicks(getClicks()+1);
        System.out.print("SIZE BUTTON CLICKED");
        
        if (getClicks()%3==0) {
        	//Decreases circle size while staying in the center
        	circle.setCircleSize(circle.getCircleSize()-100);
        	circle.setCirclePos(circle.getCircleXPos()+50, circle.getCircleYPos()+50);
        	System.out.println(", circle decreased");
        } else {
        	//Centers the circle position when increased,
        	//And restricts the circle from growing outside the space
        	xSize=-25; ySize=-25;
        		if(circle.getCircleXPos()-25<=15) xSize=0;
        		if(circle.getCircleYPos()-25<=30) ySize=0;
        		if(circle.getCircleXPos()+circle.getCircleSize()+25>=765) xSize=-50;
        		if(circle.getCircleYPos()+circle.getCircleSize()+25>=365) ySize=-50;
        	circle.setCirclePos(circle.getCircleXPos()+xSize, circle.getCircleYPos()+ySize);
        	
        	circle.setCircleSize(circle.getCircleSize()+50);
        	System.out.println(", circle increased");
        }
        circle.repaint();
    }
}