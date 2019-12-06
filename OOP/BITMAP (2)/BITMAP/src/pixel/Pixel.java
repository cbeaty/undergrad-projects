package pixel;

public class Pixel {
    private int rgb;
    public Pixel() {
        rgb = 16777215; //Makes the default pixel value white
    }
    public void setRed(int r) {
        if (r < 0 || r > 255) { //Makes it so that r is between 0 - 255
            throw new IllegalArgumentException();     
        }
        this.rgb = r;
    }
    public int getRed() {
        int mask = 0b00000000000000000000000011111111;
        int temp = this.rgb & mask; //Removes everything but the red section of the 32-bit int
        return temp;
    }
    public void setGreen(int g) {
        if (g < 0 || g > 255) { //Makes it so that g is between 0 - 255
            throw new IllegalArgumentException();     
        }
        int r = getRed(); //Gets the red value to store later
        int temp = g<<8; //Shifts g to the second section of the 32-bit int
        this.rgb = temp + r; //Makes it so that rgb has both red and green
    }
    public int getGreen() {
        int mask = 0b00000000000000001111111100000000;
        int temp = this.rgb & mask; //Removes everything but the green section of the 32-bit int
        int only_green = temp>>8; //Shifts for the green value
        return only_green;
    }
    public void setBlue(int b) {
        if (b < 0 || b > 255) { //Makes it so that b is between 0 - 255
            throw new IllegalArgumentException();     
        }
        int r = getRed(); //Gets the red value to store later
        int g = getGreen()<<8; //Isolates the green value to store later
        int temp = b<<16; //Shifts b to the third section of the 32-bit int
        this.rgb = r + g + temp; //Makes it so that rgb has all three colors (red, green, and blue)
    }
    public int getBlue() {
        int mask = 0b00000000111111110000000000000000;
        int temp = this.rgb & mask; //Removes everything but the blue section of the 32-bit int
        int only_blue = temp>>16; //Shifts for the blue value
        return only_blue;
    }
    public String PrintHex() {
        return String.format("#%06X", this.rgb); //Converts the rgb value to hex
    }
}