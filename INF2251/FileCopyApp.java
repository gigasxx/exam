import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
class FileCopier {
    public void copyFile(String sourceFile) throws IOException {
        FileInputStream fis = null;
        FileOutputStream fos = null;
        try {
            fis = new FileInputStream(sourceFile);
            fos = new FileOutputStream("test.txt");
            int ch;
            while ((ch = fis.read()) != -1) {
                fos.write(ch);
            }
        }
        finally {
            if (fis != null)
                fis.close();
            if (fos != null)
                fos.close();
        }
    }
}
class FileCopyFrame extends JFrame implements ActionListener {
    JLabel lbl;
    JTextField txtFile;
    JButton btnCopy;
    FileCopier copier;
    public FileCopyFrame() {
        copier = new FileCopier();
        setTitle("File Copy Program");
        setSize(400, 150);
        setLayout(new FlowLayout());
        lbl = new JLabel("Enter File Name:");
        txtFile = new JTextField(20);
        btnCopy = new JButton("Copy");
        add(lbl);
        add(txtFile);
        add(btnCopy);
        btnCopy.addActionListener(this);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }
    public void actionPerformed(ActionEvent e) {
        String sourceFile = txtFile.getText().trim();
        if (sourceFile.length() == 0) {
            JOptionPane.showMessageDialog(this, "Please enter a file name.", "Input Error", JOptionPane.ERROR_MESSAGE);
            return;
        }
        try {
            copier.copyFile(sourceFile);
            JOptionPane.showMessageDialog(this, "File copied successfully to test.txt", "Success", JOptionPane.INFORMATION_MESSAGE);
        }
        catch (FileNotFoundException ex) {
            JOptionPane.showMessageDialog(this, "File not found!", "Error", JOptionPane.ERROR_MESSAGE);
        }
        catch (IOException ex) {
            JOptionPane.showMessageDialog(this, "I/O Error : " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
        catch (Exception ex) {
            JOptionPane.showMessageDialog(this, "Unexpected Error : " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
}
public class FileCopyApp {
    public static void main(String[] args) {
        new FileCopyFrame();
    }
}
