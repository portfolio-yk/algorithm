#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

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

    fail_slot.clear();

    area_list.clear(); 
    area_list.resize(N);

    for (int i = 0; i < N; ++i) {
        area_list[i].id = i;
        area_list[i].slot_count = M;
        area_list[i].occupied = 0;

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
    T = L;
    area_list.clear(); 
    fail_slot.clear(); 

    for(int i = 0; i < N; i++) {
        Area new_area;
        new_area.id = i;
        new_area.slot_count = M;
        new_area.occupied = 0;

        for(int j = 0; j < 1000; j++) {
            new_area.slots[j].time = 0;
            new_area.slots[j].number = ""; 
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


#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

// 도우미 함수들
void p_e(int t, const char* n, RESULT_E re) {
    if (re.success == 1) cout << "200 " << t << " " << n << " 1 " << re.locname << "\n";
    else cout << "200 " << t << " " << n << " 0\n";
}

void p_s(int t, const char* s, RESULT_S rs) {
    cout << "400 " << t << " " << s << " " << rs.cnt;
    for (int i = 0; i < rs.cnt; i++) cout << " " << rs.carlist[i];
    cout << "\n";
}

int main() {
    RESULT_E re; RESULT_S rs; int rt;

    // [100] 초기화
    init(2, 6, 1213);

    p_e(14, "69K7844", enter(14, "69K7844"));
    p_e(16, "17S6185", enter(16, "17S6185"));
    p_e(53, "71X1443", enter(53, "71X1443"));
    p_s(76, "1443", search(76, "1443"));
    p_s(119, "6185", search(119, "6185"));
    cout << "300 252 69K7844 " << pullout(252, "69K7844") << "\n";
    cout << "300 360 69K7844 " << pullout(360, "69K7844") << "\n";
    cout << "300 455 71X1443 " << pullout(455, "71X1443") << "\n";
    p_e(467, "92B1443", enter(467, "92B1443"));
    p_s(476, "9642", search(476, "9642"));
    p_s(491, "6185", search(491, "6185"));
    p_s(539, "1443", search(539, "1443"));
    p_e(572, "07Y7844", enter(572, "07Y7844"));
    cout << "300 682 07Y7844 " << pullout(682, "07Y7844") << "\n";
    p_e(711, "44K8100", enter(711, "44K8100"));
    p_s(794, "1443", search(794, "1443"));
    cout << "300 873 44K8100 " << pullout(873, "44K8100") << "\n";
    p_s(899, "1443", search(899, "1443"));
    p_e(1071, "08D1443", enter(1071, "08D1443"));
    cout << "300 1087 08D1443 " << pullout(1087, "08D1443") << "\n";
    p_e(1097, "24P2346", enter(1097, "24P2346"));
    cout << "300 1212 92B1443 " << pullout(1212, "92B1443") << "\n";
    p_e(1360, "63F1443", enter(1360, "63F1443"));
    p_e(1390, "17D2593", enter(1390, "17D2593"));
    p_e(1392, "94W6185", enter(1392, "94W6185"));
    cout << "300 1420 63F1443 " << pullout(1420, "63F1443") << "\n";
    cout << "300 1430 17D2593 " << pullout(1430, "17D2593") << "\n";
    cout << "300 1477 17S6185 " << pullout(1477, "17S6185") << "\n"; // -2453
    cout << "300 1641 24P2346 " << pullout(1641, "24P2346") << "\n";
    cout << "300 1679 94W6185 " << pullout(1679, "94W6185") << "\n";
    cout << "300 1743 17D2593 " << pullout(1743, "17D2593") << "\n";
    cout << "300 1832 71X1443 " << pullout(1832, "71X1443") << "\n";
    cout << "300 1881 44K8100 " << pullout(1881, "44K8100") << "\n";
    p_e(1954, "35Z4992", enter(1954, "35Z4992"));
    p_e(2045, "57S6033", enter(2045, "57S6033"));
    cout << "300 2068 35Z4992 " << pullout(2068, "35Z4992") << "\n";
    p_e(2095, "75I2346", enter(2095, "75I2346"));
    p_s(2137, "6033", search(2137, "6033"));
    cout << "300 2252 71X1443 " << pullout(2252, "71X1443") << "\n";
    p_e(2311, "24K8100", enter(2311, "24K8100"));
    p_e(2373, "11S2346", enter(2373, "11S2346"));
    cout << "300 2384 75I2346 " << pullout(2384, "75I2346") << "\n";
    p_e(2572, "80V1443", enter(2572, "80V1443"));
    cout << "300 2617 24K8100 " << pullout(2617, "24K8100") << "\n";
    p_e(2619, "78Q7844", enter(2619, "78Q7844"));
    p_e(2644, "88I7159", enter(2644, "88I7159"));
    p_s(2692, "6033", search(2692, "6033"));
    p_e(2709, "28M9642", enter(2709, "28M9642"));
    cout << "300 2753 88I7159 " << pullout(2753, "88I7159") << "\n";
    cout << "300 2810 11S2346 " << pullout(2810, "11S2346") << "\n";
    p_s(2904, "7844", search(2904, "7844"));
    p_e(2933, "68D7844", enter(2933, "68D7844"));
    cout << "300 2973 80V1443 " << pullout(2973, "80V1443") << "\n";
    p_s(3062, "7844", search(3062, "7844"));
    p_e(3201, "96Z0538", enter(3201, "96Z0538"));
    p_s(3229, "7844", search(3229, "7844"));
    p_e(3336, "22E8100", enter(3336, "22E8100"));
    p_e(3404, "41M2593", enter(3404, "41M2593"));
    p_e(3407, "21P2593", enter(3407, "21P2593"));
    p_e(3517, "56I9815", enter(3517, "56I9815"));
    cout << "300 3556 28M9642 " << pullout(3556, "28M9642") << "\n";
    p_e(3672, "69U6185", enter(3672, "69U6185"));
    p_e(3796, "07V6033", enter(3796, "07V6033"));
    p_e(3803, "50U4992", enter(3803, "50U4992"));
    p_e(3804, "83A4992", enter(3804, "83A4992"));
    p_e(3852, "25G0124", enter(3852, "25G0124"));
    p_s(3933, "7844", search(3933, "7844"));
    p_e(4062, "52H2346", enter(4062, "52H2346"));
    p_e(4113, "42Q7159", enter(4113, "42Q7159"));
    p_s(4120, "2593", search(4120, "2593"));
    cout << "300 4129 68D7844 " << pullout(4129, "68D7844") << "\n";
    cout << "300 4143 07V6033 " << pullout(4143, "07V6033") << "\n";
    p_e(4174, "32Q6033", enter(4174, "32Q6033"));
    p_e(4246, "24P2346", enter(4246, "24P2346"));
    p_e(4258, "21M2346", enter(4258, "21M2346"));
    cout << "300 4343 21P2593 " << pullout(4343, "21P2593") << "\n";
    p_e(4349, "03L1443", enter(4349, "03L1443"));
    p_e(4448, "60O0538", enter(4448, "60O0538"));
    cout << "300 4468 83A4992 " << pullout(4468, "83A4992") << "\n";
    p_e(4494, "07V6033", enter(4494, "07V6033"));
    p_e(4505, "24U6185", enter(4505, "24U6185"));
    p_s(4588, "8100", search(4588, "8100"));
    p_s(4707, "2593", search(4707, "2593"));
    p_e(4728, "83F9642", enter(4728, "83F9642"));
    p_s(4842, "0124", search(4842, "0124"));
    p_s(4857, "9815", search(4857, "9815"));
    cout << "300 4903 96Z0538 " << pullout(4903, "96Z0538") << "\n"; // -3658
    cout << "300 4962 50U4992 " << pullout(4962, "50U4992") << "\n";
    p_e(5054, "03A6185", enter(5054, "03A6185"));
    p_e(5153, "39H9642", enter(5153, "39H9642"));
    p_e(5167, "02R4992", enter(5167, "02R4992"));
    p_e(5244, "46G2593", enter(5244, "46G2593"));
    p_s(5262, "8100", search(5262, "8100"));
    p_e(5389, "00Q8100", enter(5389, "00Q8100"));
    cout << "300 5483 02R4992 " << pullout(5483, "02R4992") << "\n";
    p_e(5509, "52H2346", enter(5509, "52H2346"));
    p_e(5611, "57S6033", enter(5611, "57S6033"));
    p_s(5627, "6033", search(5627, "6033"));
    p_e(5704, "35Z4992", enter(5704, "35Z4992"));
    p_e(5746, "50U4992", enter(5746, "50U4992"));

    return 0;
}