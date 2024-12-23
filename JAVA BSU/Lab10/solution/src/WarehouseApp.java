import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class WarehouseApp {

    private static List<String> records = new ArrayList<>();

    public static void main(String[] args) {
        // Создание главного окна
        JFrame mainFrame = new JFrame("Warehouse Management System");
        mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mainFrame.setSize(800, 600);

        // Создание меню
        JMenuBar menuBar = new JMenuBar();

        // Меню File
        JMenu fileMenu = new JMenu("File");
        JMenuItem openItem = new JMenuItem("Open...");
        JMenuItem saveItem = new JMenuItem("Save");
        JMenuItem exitItem = new JMenuItem("Exit");

        exitItem.addActionListener(e -> System.exit(0));

        openItem.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser();
            if (fileChooser.showOpenDialog(mainFrame) == JFileChooser.APPROVE_OPTION) {
                File file = fileChooser.getSelectedFile();
                try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
                    records.clear();
                    String line;
                    while ((line = reader.readLine()) != null) {
                        records.add(line);
                    }
                    JOptionPane.showMessageDialog(mainFrame, "Records loaded successfully.");
                } catch (IOException ex) {
                    JOptionPane.showMessageDialog(mainFrame, "Error loading file: " + ex.getMessage());
                }
            }
        });

        saveItem.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser();
            if (fileChooser.showSaveDialog(mainFrame) == JFileChooser.APPROVE_OPTION) {
                File file = fileChooser.getSelectedFile();
                try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
                    for (String record : records) {
                        writer.write(record);
                        writer.newLine();
                    }
                    JOptionPane.showMessageDialog(mainFrame, "Records saved successfully.");
                } catch (IOException ex) {
                    JOptionPane.showMessageDialog(mainFrame, "Error saving file: " + ex.getMessage());
                }
            }
        });

        fileMenu.add(openItem);
        fileMenu.add(saveItem);
        fileMenu.addSeparator();
        fileMenu.add(exitItem);
        menuBar.add(fileMenu);

        // Меню Edit
        JMenu editMenu = new JMenu("Edit");
        JMenuItem addItem = new JMenuItem("Add Record");
        JMenuItem deleteItem = new JMenuItem("Delete Record");

        deleteItem.addActionListener(e -> {
            if (!records.isEmpty()) {
                records.remove(records.size() - 1);
                JOptionPane.showMessageDialog(mainFrame, "Last record deleted.");
            } else {
                JOptionPane.showMessageDialog(mainFrame, "No records to delete.");
            }
        });

        editMenu.add(addItem);
        editMenu.add(deleteItem);
        menuBar.add(editMenu);

        mainFrame.setJMenuBar(menuBar);

        // Строка статуса
        JLabel statusBar = new JLabel("Welcome to the Warehouse Management System");
        statusBar.setBorder(BorderFactory.createEtchedBorder());
        mainFrame.add(statusBar, BorderLayout.SOUTH);

        // Клиентская область - форма для ввода данных
        JPanel clientPanel = new JPanel();
        clientPanel.setLayout(new GridLayout(7, 2, 5, 5));

        // Поля ввода
        clientPanel.add(new JLabel("Warehouse Number:"));
        JTextField warehouseField = new JTextField();
        clientPanel.add(warehouseField);

        clientPanel.add(new JLabel("Product Code:"));
        JTextField codeField = new JTextField();
        clientPanel.add(codeField);

        clientPanel.add(new JLabel("Product Name:"));
        JTextField nameField = new JTextField();
        clientPanel.add(nameField);

        clientPanel.add(new JLabel("Date of Arrival (YYYY-MM-DD):"));
        JTextField dateField = new JTextField();
        clientPanel.add(dateField);

        clientPanel.add(new JLabel("Storage Duration (days):"));
        JTextField durationField = new JTextField();
        clientPanel.add(durationField);

        clientPanel.add(new JLabel("Quantity:"));
        JTextField quantityField = new JTextField();
        clientPanel.add(quantityField);

        clientPanel.add(new JLabel("Price per Unit:"));
        JTextField priceField = new JTextField();
        clientPanel.add(priceField);

        mainFrame.add(clientPanel, BorderLayout.CENTER);

        // Кнопка для сохранения записи
        JButton saveButton = new JButton("Save Record");
        saveButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // Обработка сохранения данных
                String warehouse = warehouseField.getText();
                String code = codeField.getText();
                String name = nameField.getText();
                String date = dateField.getText();
                String duration = durationField.getText();
                String quantity = quantityField.getText();
                String price = priceField.getText();

                if (warehouse.isEmpty() || code.isEmpty() || name.isEmpty() || date.isEmpty() ||
                        duration.isEmpty() || quantity.isEmpty() || price.isEmpty()) {
                    statusBar.setText("Please fill in all fields.");
                } else {
                    String record = warehouse + "," + code + "," + name + "," + date + "," + duration + "," + quantity + "," + price;
                    records.add(record);
                    statusBar.setText("Record saved: " + name);
                }
            }
        });
        mainFrame.add(saveButton, BorderLayout.NORTH);

        // Кнопка для вывода записей
        JButton displayButton = new JButton("Display Records");
        displayButton.addActionListener(e -> {
            StringBuilder recordDisplay = new StringBuilder();
            for (String record : records) {
                recordDisplay.append(record).append("\n");
            }
            JOptionPane.showMessageDialog(mainFrame, recordDisplay.length() > 0 ? recordDisplay.toString() : "No records available.");
        });
        mainFrame.add(displayButton, BorderLayout.EAST);

        mainFrame.setVisible(true);
    }
}