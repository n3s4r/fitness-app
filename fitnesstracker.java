import java.util.*;
import java.io.*;

public class FitnessTracker {
    // Equivalent to C++ struct
    static class Entry {
        String name;
        int calories;
        int protein;

        Entry(String name, int calories, int protein) {
            this.name = name;
            this.calories = calories;
            this.protein = protein;
        }
    }

    private static final int MAX = 100;
    private static ArrayList<Entry> food = new ArrayList<>();
    private static int calorieGoal = 2500;
    private static int workoutBurn = 0;
    private static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.print("Enter today's date (YYYY-MM-DD): ");
        String date = sc.nextLine();

        loadFromFile(date);

        while (true) {
            System.out.println("\n====== ADVANCED FITNESS TRACKER ======");
            System.out.println("1. Add Food");
            System.out.println("2. Add Workout (Calories Burned)");
            System.out.println("3. View Daily Summary");
            System.out.println("4. BMI Calculator");
            System.out.println("5. Weekly Report");
            System.out.println("6. Save & Exit");
            System.out.print("Choice: ");

            int choice = -1;
            if (sc.hasNextInt()) {
                choice = sc.nextInt();
                sc.nextLine(); // Consume newline
            } else {
                sc.nextLine(); // Clear invalid input
            }

            switch (choice) {
                case 1 -> addFood();
                case 2 -> addWorkout();
                case 3 -> viewSummary();
                case 4 -> bmiCalculator();
                case 5 -> weeklyReport();
                case 6 -> {
                    saveToFile(date);
                    System.out.println("Data saved. Stay shredded 💪");
                    return;
                }
                default -> System.out.println("Invalid option!");
            }
        }
    }

    /* Add Food */
    public static void addFood() {
        if (food.size() >= MAX) {
            System.out.println("Limit reached.");
            return;
        }

        System.out.print("Food name: ");
        String name = sc.nextLine();

        System.out.print("Calories: ");
        int calories = sc.nextInt();

        System.out.print("Protein (g): ");
        int protein = sc.nextInt();
        sc.nextLine(); // Consume newline

        food.add(new Entry(name, calories, protein));
    }

    /* Add Workout */
    public static void addWorkout() {
        System.out.print("Calories burned in workout: ");
        int burn = sc.nextInt();
        sc.nextLine(); // Consume newline
        workoutBurn += burn;
    }

    /* Calculation Helpers */
    public static int totalCalories() {
        return food.stream().mapToInt(e -> e.calories).sum();
    }

    public static int totalProtein() {
        return food.stream().mapToInt(e -> e.protein).sum();
    }

    /* View Summary */
    public static void viewSummary() {
        int intake = totalCalories();
        int net = intake - workoutBurn;

        System.out.println("\n--- DAILY SUMMARY ---");
        System.out.println("Total Calories: " + intake + " kcal");
        System.out.println("Workout Burned: " + workoutBurn + " kcal");
        System.out.println("Net Calories: " + net + " kcal");
        System.out.println("Total Protein: " + totalProtein() + " g");
        System.out.println("Calorie Goal: " + calorieGoal + " kcal");
        System.out.println("Remaining: " + (calorieGoal - net) + " kcal");
    }

    /* BMI Calculator */
    public static void bmiCalculator() {
        System.out.print("Enter weight (kg): ");
        double weight = sc.nextDouble();

        System.out.print("Enter height (m): ");
        double height = sc.nextDouble();
        sc.nextLine(); // Consume newline

        double bmi = weight / (height * height);

        System.out.printf("Your BMI: %.2f\n", bmi);

        if (bmi < 18.5) System.out.println("Underweight");
        else if (bmi < 25) System.out.println("Normal");
        else if (bmi < 30) System.out.println("Overweight");
        else System.out.println("Obese");
    }

    /* Save Data */
    public static void saveToFile(String date) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(date + ".txt"))) {
            writer.println(food.size() + " " + workoutBurn);
            for (Entry e : food) {
                // Replacing spaces in food names with underscores to prevent parsing errors
                writer.println(e.name.replace(" ", "_") + " " + e.calories + " " + e.protein);
            }
        } catch (IOException e) {
            System.out.println("Error saving file.");
        }
    }

    /* Load Data */
    public static void loadFromFile(String date) {
        File file = new File(date + ".txt");
        if (!file.exists()) return;

        try (Scanner fileScanner = new Scanner(file)) {
            if (fileScanner.hasNextInt()) {
                int count = fileScanner.nextInt();
                workoutBurn = fileScanner.nextInt();
                food.clear();

                for (int i = 0; i < count; i++) {
                    String name = fileScanner.next().replace("_", " ");
                    int cal = fileScanner.nextInt();
                    int prot = fileScanner.nextInt();
                    food.add(new Entry(name, cal, prot));
                }
            }
        } catch (FileNotFoundException e) {
            // Silently fail if no file exists for today
        }
    }

    /* Weekly Report */
    public static void weeklyReport() {
        int weeklyCalories = 0;
        int weeklyProtein = 0;

        System.out.println("Enter 7 dates (YYYY-MM-DD):");
        for (int i = 0; i < 7; i++) {
            System.out.print("Date " + (i + 1) + ": ");
            String date = sc.nextLine();
            File file = new File(date + ".txt");

            if (!file.exists()) {
                System.out.println("No data for " + date);
                continue;
            }

            try (Scanner fileScanner = new Scanner(file)) {
                int count = fileScanner.nextInt();
                fileScanner.nextInt(); // skip workoutBurn

                for (int j = 0; j < count; j++) {
                    fileScanner.next(); // skip name
                    weeklyCalories += fileScanner.nextInt();
                    weeklyProtein += fileScanner.nextInt();
                }
            } catch (Exception e) {
                System.out.println("Error reading " + date);
            }
        }

        System.out.println("\n--- WEEKLY REPORT ---");
        System.out.println("Total Weekly Calories: " + weeklyCalories + " kcal");
        System.out.println("Average Per Day: " + (weeklyCalories / 7) + " kcal");
        System.out.println("Total Weekly Protein: " + weeklyProtein + " g");
        System.out.println("Average Protein Per Day: " + (weeklyProtein / 7) + " g");
    }
}
