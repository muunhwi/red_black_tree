- **대략 10000 개의 데이터를 삽입, 삭제 996회 수행 표**

```cpp
                       Name |              Average |              Max     |                  Min |                 Call |

BTREE RANDOM INSERT         |             1371.0㎲ |            10762.3㎲ |              807.3㎲ |                  996 |
RBTREE RANDOM INSERT        |             1544.4㎲ |            15062.3㎲ |              943.9㎲ |                  996 |

BTREE RANDOM DELETE         |             1484.4㎲ |            18421.2㎲ |              920.3㎲ |                  996 |
RBTREE RANDOM DELETE        |             1404.0㎲ |            11397.1㎲ |              843.7㎲ |                  996 |

BTREE ASC INSERT            |           146343.4㎲ |           338039.5㎲ |           111652.0㎲ |                  996 |
RBTREE ASC INSERT           |             1220.6㎲ |            10729.2㎲ |              767.7㎲ |                  996 |

BTREE DESC DELETE           |           583424.1㎲ |          1497712.7㎲ |           190704.5㎲ |                  996 |
RBTREE DESC DELETE          |              786.9㎲ |             3035.9㎲ |              427.1㎲ |                  996 |

```

- 레드 블랙 트리(RBTree)와 이진 탐색 트리(BTree)의 성능을 비교하겠습니다.
    1. **랜덤 삽입 (Random Insert)**
        - **BTREE RANDOM INSERT:** 평균 1371.0㎲
        - **RBTREE RANDOM INSERT:** 평균 1544.4㎲
        - **비교:** RBTREE의 성능이 약 1.13배 더 나쁨 (1544.4 / 1371.0)
    2. **랜덤 삭제 (Random Delete)**
        - **BTREE RANDOM DELETE:** 평균 1484.4㎲
        - **RBTREE RANDOM DELETE:** 평균 1404.0㎲
        - **비교:** RBTREE의 성능이 약 1.06배 더 좋음 (1484.4 / 1404.0)
    3. **순차 삽입 (Ascending Insert)**
        - **BTREE ASC INSERT:** 평균 146343.4㎲
        - **RBTREE ASC INSERT:** 평균 1220.6㎲
        - **비교:** RBTREE의 성능이 약 119.91배 더 좋음 (146343.4 / 1220.6)
    4. **내림차순 삭제 (Descending Delete)**
        - **BTREE DESC DELETE:** 평균 583424.1㎲
        - **RBTREE DESC DELETE:** 평균 786.9㎲
        - **비교:** RBTREE의 성능이 약 741.29배 더 좋음 (583424.1 / 786.9)
- 정리
    
    레드 블랙 트리와 이진 탐색 트리의 성능을 비교한 결과는 다음과 같습니다:
    
    - **랜덤 삽입:** 이진 탐색 트리(BTree)가 약 1.13배 더 성능이 좋음
    - **순차 삽입:** 레드 블랙 트리(RBTree)가 약 119.91배 더 성능이 좋음
    - **랜덤 삭제:** 레드 블랙 트리(RBTree)가 약 1.06배 더 성능이 좋음
    - **내림차순 삭제:** 레드 블랙 트리(RBTree)가 약 741.29배 더 성능이 좋음
