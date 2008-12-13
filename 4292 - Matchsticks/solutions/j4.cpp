#include <vector>
#include <assert.h>
#include <stdio.h>

using namespace std;

int main() {
  int cases, songs, histsize;
  
  scanf("%d", &cases);
  for (int i = 0; i < cases; ++i) {
    scanf("%d %d", &songs, &histsize);
    vector<int> last_occurrence(songs + 1, -1);
    vector<pair<int, int> > ranges;
    ranges.push_back(make_pair(0, songs));
    
    for (int i = 0; i < histsize; i++) {
      int song;
      scanf("%d", &song);
      assert(song >= 1 && song <= songs);
      int end = i;
      int start = last_occurrence[song];
      if (start != -1 && end - start < songs) {
        start %= songs; end %= songs;
        if (end <= start) {
          vector<pair<int, int> > new_ranges;
          for (uint j = 0; j < ranges.size(); j++) {
            pair<int, int> r = make_pair(ranges[j].first,
                                         min(end, ranges[j].second)),
              r2 = make_pair(max(ranges[j].first, start),
                             ranges[j].second);
            if (r.second > r.first) new_ranges.push_back(r);
            if (r2.second > r2.first) new_ranges.push_back(r2);
          }
          ranges.swap(new_ranges);
        } else {
          for (uint j = 0; j < ranges.size(); j++) {
            ranges[j].first = max(start, ranges[j].first);
            ranges[j].second = min(end, ranges[j].second);
            if(ranges[j].first >= ranges[j].second) {
              ranges.erase(ranges.begin() + j);
              j--;
            }
          }
        }
      }
      last_occurrence[song] = i;
    }
    
    int count = 0;
    for (uint i = 0; i < ranges.size(); i++)
      count += ranges[i].second - ranges[i].first;
    printf("%d\n", count);
  }
  return 0;
}
