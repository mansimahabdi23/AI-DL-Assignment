import java.util.*;

class Rule {
    List<String> premises;
    String conclusion;

    Rule(List<String> premises, String conclusion) {
        this.premises = premises;
        this.conclusion = conclusion;
    }

    boolean isApplicable(Set<String> facts) {
        return facts.containsAll(premises);
    }
}

public class ForwardChaining {
    private Set<String> facts = new HashSet<>();
    private List<Rule> rules = new ArrayList<>();

    public void addFact(String fact) {
        facts.add(fact);
    }

    public void addRule(List<String> premises, String conclusion) {
        rules.add(new Rule(premises, conclusion));
    }

    public boolean infer(String goal) {
        boolean newFactAdded;

        do {
            newFactAdded = false;

            for (Rule rule : rules) {
                if (rule.isApplicable(facts) && !facts.contains(rule.conclusion)) {
                    System.out.println("Applied rule: " + rule.premises + " -> " + rule.conclusion);
                    facts.add(rule.conclusion);
                    newFactAdded = true;

                    if (rule.conclusion.equals(goal)) {
                        System.out.println("Goal " + goal + " reached!");
                        return true;
                    }
                }
            }
        } while (newFactAdded);

        System.out.println("Goal " + goal + " not reachable.");
        return false;
    }

    public static void main(String[] args) {
        ForwardChaining fc = new ForwardChaining();

        // Initial facts
        fc.addFact("A");
        fc.addFact("B");

        // Rules
        fc.addRule(Arrays.asList("A", "B"), "C");
        fc.addRule(Arrays.asList("C"), "D");
        fc.addRule(Arrays.asList("D", "B"), "E");

        // Goal
        String goal = "E";
        fc.infer(goal);
    }
}
