package js;
import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONObject;
import java.util.*;

public class HelloWorld {
    public static void main(String[] args) {
        Group group = new Group();
        group.setId(0L);
        group.setName("admin");

        User guestUser = new User();
        guestUser.setId(2L);
        guestUser.setName("guest");

        User rootUser = new User();
        rootUser.setId(3L);
        rootUser.setName("root");

        group.addUser(guestUser);
        group.addUser(rootUser);
        
        String jsonString = JSON.toJSONString(group);
        System.out.println(jsonString);
        
        JSONObject a = JSON.parseObject(jsonString);
        Group b = JSON.parseObject(jsonString, Group.class);
    }
}

class Group {

    private Long       id;
    private String     name;
    private List<User> users = new ArrayList<User>();

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public List<User> getUsers() {
        return users;
    }

    public void setUsers(List<User> users) {
        this.users = users;
    }

    public void addUser(User user) {
        users.add(user);
    }
}

class User {

    private Long   id;
    private String name;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}