package lom;
import lombok.ToString;

@ToString(exclude = {"id","name"})
public class User {
    private Integer id;
    private String name;
    private String phone;
    User(Integer id, String name, String phone) {
        this.id = id;
        this.name = name;
        this.phone = phone;
    }
    public static void main(String[] args) {
        User user = new User(1, "gxg", "1");
        System.out.println(user);
    }
}