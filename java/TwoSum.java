import java.util.Arrays;
import java.util.Map;
import java.util.HashMap;

public class TwoSum {
    public int[] solution(int[] nums, int target) {
        System.out.println("nums: " + Arrays.toString(nums));
        System.out.println("target = " + target);

        Map<Integer, Integer> hash = new HashMap<>();

        for (int i=0; i<nums.length; ++i) {
            int complement = target - nums[i];
            if (hash.containsKey(complement)) {
                return new int[] {hash.get(complement), i};
            }
            hash.put(nums[i], i);
        }

        throw new IllegalArgumentException("No two sum solution");
    }

    public static void main(String[] args) {
        int[] nums = {2, 7, 11, 15};
        int target = 9;
        TwoSum twoSum = new TwoSum();
        int[] solution = twoSum.solution(nums, target);
        System.out.printf("solution: %d and %d\n", solution[0], solution[1]);
    }
}
