<h1><strong >합병정렬과 퀵정렬 구현하기</strong></h1>
<hr>

## 문제 1 (합병정렬)
N개의 양의 정수를 입력(중복 허용)받아 정렬하는 프로그램을 작성하시오. 정렬은 단일연결리스트를 이용하여 합병정렬을 구현하여 사용한다. 

1. ### 구현 조건
- 크기가 N인 단일연결리스트를 동적 할당하여, 입력된 양의 정수 저장 (입력 정수는 중복 허용)
- mergeSort(L) 함수: 단일연결리스트 L의 원소들을 합병정렬하여 정렬된 결과를 오름차순으로 출력
- merge(L1, L2) 함수: mergeSort에 호출되어 두 개의 정렬된 단일연결리스트 L1과 L2를 합병한 하나의 단일연결리스트를 반환. 합병을 위해서 새로운 공간을 할당하면 안되고, L1과 L2 노드들의 링크만 변화시켜서 합병.
- mg-partition(L, k) 함수: 단일연결리스트 L과 양의 정수 k를 입력받아서 L을 크기가 k이고 |L|-k인 두 개의 부분리스트 L1과 L2로 분할하여 (L1, L2)를 반환. 여기서 |L|은 L의 크기. 분할 시에도 추가로 공간을 할당해서 사용하지 않고, L의 공간을 그대로 사용해서 분할.

2. ### 예시

|입력 예시| 출력 예시|
|---|---|
|3	    	↦ N|□1 4 9				↦ 정렬 결과|
|4 9 1| |

---

## 문제 2 (퀵정렬)
N개의 양의 정수를 입력(중복 허용)받아 정렬하는 프로그램을 작성하시오. 정렬은 아래에 명시된 퀵 정렬을 구현하여 사용한다. 

1. ### 구현 조건
- 크기가 N인 배열을 동적 할당하여, 입력된 양의 정수 저장 (입력 정수는 중복 허용)
- 기준값(pivot)을 정할 때, 다음의 방법을 이용한다:
    1. 입력된 수들 중에서 3개의 수를 랜덤하게 선택한다. (즉, 입력배열의 l번째 수부터 r번째 수 중에서 3개의 수를 랜덤하게 선택)
    2. 랜덤하게 선택된 3개의 수 중에서 중간값(median)을 구하여 이를 pivot으로 한다.
    3. pivot을 정하는 부분을 partition함수 내에서 처리해도 된다. 혹은, 힌트에 주어진 알고리즘에서 처럼 pivot을 정하고 그 인덱스를 반환하는 함수 find_pivot_index를 따로 작성해서 partiton에 pivot index를 인자로 넘겨줘도 된다.
- partition 함수의 반환 값은 두 인덱스인 (a,b)로 partition의 결과로, 배열의 l번째 수부터 a-1번째 수는 pivot보다 작은 값을 갖고, 배열의 a번째부터 b번째 수는 pivot과 같은 값을 갖고, b+1번째부터 r번째 수는 pivot보다 큰 값을 갖게 된다. (즉, 이후 호출되는 재귀함수는 l부터 a-1까지 배열에 대해서와 b+1부터 r까지의 배열에 대해서 다루고, pivot과 같은 값들인 a부터 b번째 값들은 재귀에서 제외된다.)

2. ### 예시

|입력 예시| 출력 예시|
|---|---|
|8				↦ N|□3 8 20 29 31 48 65 73	↦ 정렬 결과|
|73 65 48 31 29 20 8 3| |