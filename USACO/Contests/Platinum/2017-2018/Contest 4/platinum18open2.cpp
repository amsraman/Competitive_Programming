#include "grader.h"
#define BLOCK 1000

void helpBessie(int ID) {
    int n = getTrainLength();
    int k = getWindowLength();
    int ind = getCurrentCarIndex();
    int pass = getCurrentPassIndex();

    if(pass == 0) {
        int low_pointer = get(5498), high_pointer = get(5499);
        if(get(low_pointer + 1) <= ind - k) {
            low_pointer += 2;
        }
        while(high_pointer > low_pointer && get(high_pointer - 2) > ID) {
            high_pointer -= 2;
        }
        int lst_index = (high_pointer > 0 ? get(high_pointer - 1) : 0);
        // Two indices i, j are considered equivalent iff i and j are in the same block, AND on the same side of k % BLOCK
        if(low_pointer == high_pointer || (lst_index / BLOCK != ind / BLOCK) || ((lst_index % BLOCK < k % BLOCK) != (ind % BLOCK < k % BLOCK))) {
            if(low_pointer == high_pointer) {
                low_pointer = high_pointer = 0;
            }
            set(high_pointer++, ID);
            set(high_pointer++, ind);
        }
        if(ind == n - 1 || (ind >= k - 1 && (ind - k + 1) % BLOCK == 0)) {
            set(4050 + (ind - k + BLOCK) / BLOCK, get(low_pointer + 1));
        }
        set(5498, low_pointer), set(5499, high_pointer);
    } else {
        // Optimization: only access 5494 if it hasn't been accessed yet in this run (i.e. global_min == 5494)
        int start_ind = get(4050);
        if(ind < start_ind) {
            return;
        } else if(ind == start_ind) {
            set(5494, INT32_MAX), set(5495, 1);
        }
        int num_written = get(5493), cur_block = get(5495), low_pointer = get(5496), high_pointer = get(5497), global_min = -1;
        if(ind <= BLOCK + get(4049 + cur_block)) {
            while(high_pointer > low_pointer && get(high_pointer - 2) > ID) {
                high_pointer -= 2;
            }
            set(high_pointer++, ID);
            set(high_pointer++, ind);
        } else {
            if(global_min == -1) {
                global_min = get(5494);
            }
            global_min = min(global_min, ID);
            set(5494, global_min);
        }
        if(num_written + k - 1 == ind) {
            while(low_pointer < high_pointer && get(low_pointer + 1) < num_written) {
                low_pointer += 2;
            }
            if(global_min == -1) {
                global_min = get(5494);
            }
            shoutMinimum(min(global_min, get(low_pointer)));
            ++num_written;
        }
        while(cur_block * BLOCK + k - 1 < n && ind == get(4050 + cur_block)) {
            if(global_min == -1) {
                global_min = get(5494);
            }
            while(num_written < cur_block * BLOCK) {
                while(low_pointer < high_pointer && get(low_pointer + 1) < num_written) {
                    low_pointer += 2;
                }
                shoutMinimum(min(global_min, get(low_pointer)));
                ++num_written;
            }
            low_pointer = high_pointer = 0;
            set(high_pointer++, ID);
            set(high_pointer++, ind);
            set(5494, INT32_MAX);
            ++cur_block;
        }
        set(5493, num_written), set(5495, cur_block), set(5496, low_pointer), set(5497, high_pointer);
    }
}
