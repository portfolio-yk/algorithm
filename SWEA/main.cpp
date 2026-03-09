#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

char alphabet[] = {'A', 'B', 'C'};

int T;

struct ParkCar
{
    int time;
    string number;
    string X;
    string Y;
    string Z;
};

struct Area
{
    int id;
    int slot_count;
    int occupied = 0;
    ParkCar slots[1000];
};

vector<Area> area_list;
vector<ParkCar> fail_slot;

struct RESULT_E
{
    int success;
    char locname[5];
};

struct RESULT_S
{
    int cnt;
    char carlist[5][8];
};

int processTowing(int mTime, char mCarNo[]) {
    int myCar = 0;
    for (int i = 0; i < area_list.size(); ++i) {
        for (int j = 0; j < area_list[i].slot_count; ++j) {
            if (!area_list[i].slots[j].number.empty() && mTime - area_list[i].slots[j].time >= T) {
                if(area_list[i].slots[j].number == mCarNo) {
                    myCar = 1;
                }
                fail_slot.push_back(area_list[i].slots[j]);
                
                area_list[i].slots[j].number.clear();
                area_list[i].slots[j].X.clear();
                area_list[i].slots[j].Y.clear();
                area_list[i].slots[j].Z.clear();
                area_list[i].slots[j].time = 0;
                
                area_list[i].occupied--;
            }
        }
    }
    return myCar;
}

void clear(int N, int M, int L) {
    T = L; 

    // 2. 견인 리스트 비우기
    fail_slot.clear();

    // 3. 구역 리스트 초기화 및 재할당
    area_list.clear(); // 기존 데이터 완전 삭제
    area_list.resize(N); // 새로운 구역 개수만큼 확장

    // 4. 각 구역 내부 슬롯 초기화
    for (int i = 0; i < N; ++i) {
        area_list[i].id = i;
        area_list[i].slot_count = M;
        area_list[i].occupied = 0;

        // Area 구조체 내의 slots[1000] 배열 초기화
        for (int j = 0; j < 1000; ++j) {
            area_list[i].slots[j].time = 0;
            area_list[i].slots[j].number.clear();
            area_list[i].slots[j].X.clear();
            area_list[i].slots[j].Y.clear();
            area_list[i].slots[j].Z.clear();
        }
    }
}

void init(int N, int M, int L)
{
    // 1. 기존 데이터 완전 초기화
    T = L;
    area_list.clear(); // 이전 테스트 케이스의 구역 정보를 삭제
    fail_slot.clear(); // 이전 견인 기록 삭제

    // 2. 구역(Area) 생성 및 추가
    for(int i = 0; i < N; i++) {
        Area new_area;
        new_area.id = i;
        new_area.slot_count = M;
        new_area.occupied = 0;

        // 3. 내부 slots 배열의 string/int 초기화
        for(int j = 0; j < 1000; j++) {
            new_area.slots[j].time = 0;
            new_area.slots[j].number = ""; // 명시적 빈 문자열 초기화
            new_area.slots[j].X = "";
            new_area.slots[j].Y = "";
            new_area.slots[j].Z = "";
        }
        
        area_list.push_back(new_area);
    }
}

RESULT_E enter(int mTime, char mCarNo[])
{
    RESULT_E res_e;

    res_e.success = 0;

    int isTowing = processTowing(mTime, mCarNo);

    
    for (auto it = fail_slot.begin(); it != fail_slot.end(); ++it) {
        if (it->number == mCarNo) {
            fail_slot.erase(it);
            break;
        }
    }
    
    

    //정렬 (최적화 필요)
    auto it = min_element(area_list.begin(), area_list.end(), [](const Area& a, const Area& b) {
        int a_empty = a.slot_count - a.occupied;
        int b_empty = b.slot_count - b.occupied;

        if (a_empty != b_empty) {
            return a_empty > b_empty;
        }
        return a.id < b.id;
    });


    if (it != area_list.end() && (it->slot_count - it->occupied) > 0) {
        for (int i = 0; i < it->slot_count; ++i) {
            if (it->slots[i].number[0] == '\0') { 
                string fullNo(mCarNo); 
                
                it->slots[i].time = mTime;
                it->slots[i].number = fullNo;
                it->slots[i].X = fullNo.substr(0, 2); 
                it->slots[i].Y = fullNo.substr(2, 1); 
                it->slots[i].Z = fullNo.substr(3, 4); 
                it->occupied += 1;

                //A001 만들기
                char area_letter = 'A' + it->id;
                snprintf(res_e.locname, sizeof(res_e.locname), "%c%03d", area_letter, i);
                res_e.success = 1; 
                return res_e;      
            }
        }
    }

    return res_e;
}

int pullout(int mTime, char mCarNo[])
{
    processTowing(mTime, "");

    string targetNo(mCarNo);

    for (int i = 0; i < area_list.size(); ++i) {
        for (int j = 0; j < area_list[i].slot_count; ++j) {
            if (area_list[i].slots[j].number == targetNo) {
                int parked_duration = mTime - area_list[i].slots[j].time;

                area_list[i].slots[j].number.clear();
                area_list[i].occupied--;

                return parked_duration; 
            }
        }
    }

    for (auto it = fail_slot.begin(); it != fail_slot.end(); ++it) {
        if (it->number == targetNo) {
            int parked_duration = T;
            int towing_duration = mTime - (it->time + T);
            
            int result = (parked_duration + towing_duration * 5) * (-1);

            fail_slot.erase(it);

            return result; 
        }
    }

    
    return -1; 
}



RESULT_S search(int mTime, char mStr[]) {
    processTowing(mTime, "");

    struct SearchItem {
        string fullNumber;
        string X, Y;
    };
    RESULT_S res_s;
    res_s.cnt = 0;
    string targetZ(mStr);

    vector<SearchItem> parked_found;
    vector<SearchItem> towed_found;

    for (const auto& area : area_list) {
        for (int i = 0; i < area.slot_count; ++i) {
            if (!area.slots[i].number.empty() && area.slots[i].Z == targetZ) {
                parked_found.push_back({area.slots[i].number, area.slots[i].X, area.slots[i].Y});
            }
        }
    }

    auto compareFunc = [](const SearchItem& a, const SearchItem& b) {
        if (a.X != b.X) return stoi(a.X) < stoi(b.X);
        return a.Y < b.Y;                            
    };

    sort(parked_found.begin(), parked_found.end(), compareFunc);

    int fill_idx = 0;
    for (; fill_idx < parked_found.size() && fill_idx < 5; ++fill_idx) {
        strcpy(res_s.carlist[fill_idx], parked_found[fill_idx].fullNumber.c_str());
    }

    if (fill_idx < 5) {
        for (const auto& car : fail_slot) {
            if (car.Z == targetZ) {
                towed_found.push_back({car.number, car.X, car.Y});
            }
        }
        sort(towed_found.begin(), towed_found.end(), compareFunc);

        for (int i = 0; i < towed_found.size() && fill_idx < 5; ++i, ++fill_idx) {
            strcpy(res_s.carlist[fill_idx], towed_found[i].fullNumber.c_str());
        }
    }

    res_s.cnt = fill_idx;
    return res_s;
}

#include<iostream>

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#define CMD_INIT            (100)
#define CMD_ENTER           (200)
#define CMD_PULL_OUT        (300)
#define CMD_SEARCH          (400)

// struct RESULT_E
// {
//     int success;
//     char locname[5];
// };

// struct RESULT_S
// {
//     int cnt;
//     char carlist[5][8];
// };

// extern void init(int N, int M, int L);
// extern RESULT_E enter(int mTime, char mCarNo[]);
// extern int pullout(int mTime, char mCarNo[]);
// extern RESULT_S search(int mTime, char mStr[]);

static bool run()
{
    int Q, N, M, L;
    int mTime;

    char mCarNo[8];
    char mStr[5];

    int ret = -1, ans;

    RESULT_E res_e;
    RESULT_S res_s;

    scanf("%d", &Q);

    bool okay = false;

    for (int q = 0; q < Q; ++q)
    {
        int cmd;
        scanf("%d", &cmd);
        switch(cmd)
        {
        case CMD_INIT:
            scanf("%d %d %d", &N, &M, &L);
            init(N, M, L);
            okay = true;
            cout << "??" << "\n";
            break;      
        case CMD_ENTER:
            scanf("%d %s", &mTime, mCarNo);
            res_e = enter(mTime, mCarNo);
            scanf("%d", &ans);
            if (res_e.success != ans) {
                okay = false;
                cout << "왜" << mTime << " " << mCarNo;
            }
                
            if (ans == 1)
            {
                scanf("%s", mStr);
                if (strcmp(res_e.locname, mStr) != 0) {
                    cout << "왜1" << " " << res_e.locname << mStr << " " << mTime ;
                    okay = false;
                }
            }
            break;
        case CMD_PULL_OUT:
            scanf("%d %s", &mTime, mCarNo);
            ret = pullout(mTime, mCarNo);
            scanf("%d", &ans);
            if (ret != ans) {
                okay = false;
                cout << "왜2" << mStr;
            }
            break;
        case CMD_SEARCH:
            scanf("%d %s", &mTime, mStr);
            res_s = search(mTime, mStr);
            scanf("%d", &ans);
            if (res_s.cnt != ans)  {
                okay = false;
                cout << "왜3" << mStr;
            }
            for (int i = 0; i < ans; ++i)
            {
                scanf("%s", mCarNo);
                strcat(mCarNo, mStr);
                if (strcmp(res_s.carlist[i], mCarNo) != 0)  {
                    okay = false;
                    cout << "왜4" << mStr;
                }
            }
            break;
        default:
            cout << "왜5" ;
            okay = false;
            break;
        }
    }
    

    return okay;
}

int main()
{
    setbuf(stdout, NULL);
    //freopen("sample_input.txt", "r", stdin);

    int TC, MARK;

    scanf("%d %d", &TC, &MARK);
    for (int tc = 1; tc <= TC; ++tc)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}