import java.util.*;

class KnowledgeBase {
    // Store relations: parent -> children
    private Map<String, List<String>> parentMap = new HashMap<>();
    // Store genders
    private Map<String, String> genderMap = new HashMap<>();

    // Add parent-child relationship
    public void addParent(String parent, String child) {
        parentMap.computeIfAbsent(parent, k -> new ArrayList<>()).add(child);
    }

    // Add gender info
    public void addGender(String person, String gender) {
        genderMap.put(person, gender);
    }

    // Get children of a person
    public List<String> getChildren(String person) {
        return parentMap.getOrDefault(person, Collections.emptyList());
    }

    // Get parents of a person
    public List<String> getParents(String person) {
        List<String> parents = new ArrayList<>();
        for (String p : parentMap.keySet()) {
            if (parentMap.get(p).contains(person)) {
                parents.add(p);
            }
        }
        return parents;
    }

    // Get grandparents
    public List<String> getGrandparents(String person) {
        List<String> grandparents = new ArrayList<>();
        for (String parent : getParents(person)) {
            grandparents.addAll(getParents(parent));
        }
        return grandparents;
    }

    // Get siblings
    public List<String> getSiblings(String person) {
        List<String> siblings = new ArrayList<>();
        for (String parent : getParents(person)) {
            for (String child : getChildren(parent)) {
                if (!child.equals(person) && !siblings.contains(child)) {
                    siblings.add(child);
                }
            }
        }
        return siblings;
    }

    // Get gender-based relation
    public String getGender(String person) {
        return genderMap.getOrDefault(person, "Unknown");
    }
}

public class FamilyTreeParsing {
    public static void main(String[] args) {
        KnowledgeBase kb = new KnowledgeBase();

        // Add relationships (KB entries)
        kb.addParent("John", "Alice");
        kb.addParent("Mary", "Alice");
        kb.addParent("John", "Bob");
        kb.addParent("Mary", "Bob");
        kb.addParent("Alice", "Charlie");
        kb.addParent("David", "Charlie");

        // Add genders
        kb.addGender("John", "Male");
        kb.addGender("Mary", "Female");
        kb.addGender("Alice", "Female");
        kb.addGender("Bob", "Male");
        kb.addGender("Charlie", "Male");
        kb.addGender("David", "Male");

        // Queries
        System.out.println("Children of John: " + kb.getChildren("John"));
        System.out.println("Parents of Alice: " + kb.getParents("Alice"));
        System.out.println("Siblings of Alice: " + kb.getSiblings("Alice"));
        System.out.println("Grandparents of Charlie: " + kb.getGrandparents("Charlie"));
    }
}
