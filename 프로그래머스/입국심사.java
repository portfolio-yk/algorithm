import java.util.*;
import java.io.*;

class Solution {
    public long solution(int n, int[] times) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        
        
        long answer = 0;
        long l = 0;
        long r = (long) times[0] * n;
        
        bw.write(String.format("%d", (int)2.5));
        bw.flush();
        
        while(l <= r) {
            long mid = (l + r) / 2;
            long c = 0;
            for(int i = 0; i < times.length; i++) {
                c += (int) (mid / times[i]);
            }
            
            if(n == c) {
                answer = mid;
                r = mid - 1;
            } else if(n > c) {
                l = mid + 1;    
            } else {
                r = mid - 1;
            } 
        }
        
        
        return answer;
    }
}