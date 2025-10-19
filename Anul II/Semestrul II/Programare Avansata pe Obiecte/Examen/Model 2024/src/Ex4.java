import java.sql.*;
import java.util.Scanner;

public class Ex4 {
    public static void main(String[] args) throws SQLException {
        Scanner sc = new Scanner(System.in);
        double s = Double.parseDouble(sc.nextLine());
        int v = Integer.parseInt(sc.nextLine());

        Connection con = DriverManager.getConnection("dbc:derby://localhost:1527/Angajati");

        String sql = "SELECT FROM DateAngajati WHERE Varsta <= ? AND Salariu >= ?";
        PreparedStatement pstmt = con.prepareStatement(sql);
        pstmt.setInt(1, v);
        pstmt.setDouble(2, s);
        ResultSet rs = pstmt.executeQuery();

        while (rs.next()) {
            System.out.println(rs.getString("CNP") + " " + rs.getString("Nume") + " " + rs.getInt("Varsta") + " " + rs.getDouble("Salariu"));
        }
    }
}