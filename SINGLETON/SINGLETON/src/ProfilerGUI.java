import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTable;

public class ProfilerGUI extends JFrame {
    private JTabbedPane tabbedPanes;

    public ProfilerGUI() throws ProfilerException {
        super("Code Profiler");
        //Creating the overall container of tabbedPanes
        tabbedPanes = new JTabbedPane();
        //Creating String column titles
        ArrayList<String> surveyCol = new ArrayList<String>();
        surveyCol.add("Profile Name"); surveyCol.add("Average Duration"); 
        surveyCol.add("Longest Duration"); surveyCol.add("Shortest Duration");
        ArrayList<String> detailCol = new ArrayList<String>();
        detailCol.add("Profile Name"); detailCol.add("Start Time");
        detailCol.add("Stop Time"); detailCol.add("Duration");
        detailCol.add("Start Message"); detailCol.add("Stop Message");
        ArrayList<String> counterCol = new ArrayList<String>();
        counterCol.add("Profile Name"); counterCol.add("Number of Times Called");
        //Get the data
        ArrayList<ArrayList<String>> surveyData = Profiler.getInstance().getSurveyData();
        ArrayList<ArrayList<String>> detailData = Profiler.getInstance().getDetailData();
        ArrayList<ArrayList<String>> counterData = Profiler.getInstance().getCounterData();
        //Convert to regular array's to make JTable happy
        String[] SC = surveyCol.toArray(new String[surveyCol.size()]);
        String[] DC = detailCol.toArray(new String[detailCol.size()]);
        String[] CC = counterCol.toArray(new String[counterCol.size()]);
        //Convert to Object array's to make JTable happy
        Object[][] SD = to2DArray(surveyData);
        Object[][] DD = to2DArray(detailData);
        Object[][] CD = to2DArray(counterData);
        //Making the Jtables
        JTable surveyTable = new JTable(SD, SC);
        JTable detailsTable = new JTable(DD, DC);
        JTable counterTable = new JTable(CD, CC);
        //Putting the tables in the scroll panes
        JScrollPane countersTab = new JScrollPane(counterTable);
        counterTable.setFillsViewportHeight(true);
        JScrollPane surveyTab = new JScrollPane(surveyTable);
        surveyTable.setFillsViewportHeight(true);
        JScrollPane detailsTab = new JScrollPane(detailsTable);
        detailsTable.setFillsViewportHeight(true);
        //Adding the the tabs to the container
        tabbedPanes.add("Counters", countersTab);
        tabbedPanes.add("Profile Survey", surveyTab);
        tabbedPanes.add("Profile Details", detailsTab);
        //Add the container to the frame
        add(tabbedPanes);
        setSize(500, 500);
        setLocation(50, 50);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    //This method converts the 2D arraylist to 2D object array for the JTable
    public Object[][] to2DArray(ArrayList<ArrayList<String>> data) {
        //Getting the Object[][] to be the same size as the arraylist
        Object[][] newData = new Object[data.size()][];
        for (int i = 0; i < newData.length; i++) {
            newData[i] = new Object[data.get(i).size()];
        }
        //Copying the data over to the Object[][]
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data.get(i).size(); j++) {
                newData[i][j] = data.get(i).get(j);
            }
        }
        return newData;
    }
}