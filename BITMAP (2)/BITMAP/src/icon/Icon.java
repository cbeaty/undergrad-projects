package icon;

import java.util.ArrayList;
import pixel.Pixel;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class Icon {
    private ArrayList<ArrayList<Pixel>> Temp_Icon;
    private int rows;
    private int cols;
    public Icon() { 
        //Default is 40      
        this.rows = 40;
        this.cols = 40;
        makeIcon(this.rows, this.cols);
    }
    public Icon(int rows, int cols) {
        //Whatever you want
        if (rows < 0 || cols < 0) {
            this.rows = 40;
            this.cols = 40;
            makeIcon(this.rows, this.cols);
        }
        else {
            this.rows = rows;
            this.cols = cols;
            makeIcon(this.rows, this.cols);
        }
    }
    public void makeIcon(int rows, int cols) {
        this.Temp_Icon = new ArrayList<ArrayList<Pixel>>(); //The full icon
        for (int i = 0; i < rows; i++) {
            this.Temp_Icon.add(new ArrayList<Pixel>()); //Creates the row of ArrayLists       
        }
        for (ArrayList<Pixel> Pixs : Temp_Icon) { 
            //Goes through each row of Temp_Icon, and creates the columns for that row
            for (int j = 0; j < cols; j++) {
                Pixs.add(new Pixel()); //Adds a pixel Temp_Icon
            }
        }
    }
    public String toString() {
        String Hex = "";
        //Goes through Temp_Icon from left to right, top to bottom
        for (int i = 0; i < this.rows; i++) {
            for (int j = 0; j < this.cols; j++) {
                Hex =  Temp_Icon.get(i).get(j).PrintHex(); //Gets the hex string from the pixel class
                System.out.print(Hex);
                System.out.print(' ');
            }
            System.out.println(' '); //New line at the end of a row
        }
        return Hex; //Needed this to create a toString() method
    }
    public void setRGB(int row, int col, int r, int g, int b) {
        //Creates a temporary pixel and changes the values of rbg
        Pixel temp = this.Temp_Icon.get(row).get(col);
        temp.setRed(r);
        temp.setGreen(g);
        temp.setBlue(b);
    }
    public byte[] FileHeader() {
        ArrayList<Byte> bytes = new ArrayList<Byte>();
        byte[] byteArray;
        bytes.add((byte)'B');
        bytes.add((byte)'M');

        bytes.add((byte)0); //Size of file in bytes, added later in the code
        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);

        bytes.add((byte)0);
        bytes.add((byte)0);

        bytes.add((byte)0);
        bytes.add((byte)0);

        bytes.add((byte)54); //Fileheader size + info data size
        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);
        //Info header
        bytes.add((byte)40);
        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);

        bytes.add((byte)this.cols);
        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);

        bytes.add((byte)this.rows);
        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);

        bytes.add((byte)1); //Planes = 1
        bytes.add((byte)0);

        bytes.add((byte)24); //bits/color = 24
        bytes.add((byte)0);

        bytes.add((byte)0); //Compression
        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);

        bytes.add((byte)(this.rows*this.cols)); //Pixel data size
        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);

        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);

        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);

        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);

        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);
        bytes.add((byte)0);
        //Goes through the Temp_Icon, left to right, bottom to top and gathers the bgr
        for (int i = this.rows - 1; i > -1 ; i--) {
            for (int j = 0; j < this.cols; j++) {
                bytes.add((byte)Temp_Icon.get(i).get(j).getBlue()); //Bitmap is backwards so need this first
                bytes.add((byte)Temp_Icon.get(i).get(j).getGreen());
                bytes.add((byte)Temp_Icon.get(i).get(j).getRed());
            }
            for (int k = 0; k < Temp_Icon.get(i).size() % 4; k++) {
                bytes.add((byte)0);
            }
        }
        bytes.set(2, (byte)bytes.size()); //Sets the size of the bytes
        bytes.set(3, (byte)(bytes.size() >> 8)); //Makes more room in case the size is too large
        bytes.set(4, (byte)(bytes.size() >> 16));
        bytes.set(5, (byte)(bytes.size() >> 24));
        byteArray = new byte[bytes.size()];
        for (int i = 0; i < bytes.size(); i++) {
            byteArray[i] = bytes.get(i);
        }
        return byteArray; //Returns the byteArray to be used in the makeFile() method
    }
    public void makeFile() {
		FileOutputStream fop = null;
		File file;
		try {
			file = new File("newfile.bmp");
			fop = new FileOutputStream(file);

			// if file doesnt exists, then create it
			if (!file.exists()) {
				file.createNewFile();
			}

			// get the content in bytes
			byte[] contentInBytes = FileHeader();

			fop.write(contentInBytes);
			fop.flush();
			fop.close();

			System.out.println("Done");

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (fop != null) {
					fop.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
    }
}
