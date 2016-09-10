package biosoperations;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class InsertServlet
 */
@WebServlet("/bios")
public class bios extends HttpServlet {
	private static final long serialVersionUID = 1L;

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try(PrintWriter out = response.getWriter()) {
			String choice = request.getParameter("choice");
			try {
				response.setContentType("text/html");
				Class.forName("com.mysql.jdbc.Driver");
				Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/github","root","");
				Statement stmt = conn.createStatement();
				System.out.println(choice);
				if(choice.equals("insert")){
					response.sendRedirect("index1.html");
				}
				else if(choice.equals("update")){
					response.sendRedirect("index2.html");
				}
				else if(choice.equals("delete")){
					response.sendRedirect("index3.html");
				}
			} catch(Exception e) { 
				out.println(e);
			}
		}
	}
   
    /**
     * @see HttpServlet#HttpServlet()
     */
    public bios() {
        super();
        // TODO Auto-generated constructor stub
    }
}

