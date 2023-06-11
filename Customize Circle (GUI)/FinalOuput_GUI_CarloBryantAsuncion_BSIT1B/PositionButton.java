package FinalOuput_GUI_CarloBryantAsuncion_BSIT1B;
import java.awt.event.ActionEvent;

class PositionButton extends Button {
  
	//Auto-generated UID, required in compilation
	private static final long serialVersionUID = -5800857451708688945L;
	//circle object declaration
	private Circle circle;

	//PositionButton constructor method
    public PositionButton(String text, Circle circle) {
        super(text);
        this.circle = circle;
    }
    
    //Takes the "centerPosition" method values from Circle when clicked
    public void actionPerformed(ActionEvent e) {
        circle.centerPosition();
        System.out.println("POSITION BUTTON CLICKED, circle moved to center");
    }
}