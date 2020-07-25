# 비트연산자를 이용해 순열을 만들어 유일성을 확인하고, 최소성을 만족시키는지 확인
# C++로도 할 수 있지만 Python 연습한다고 Python으로 도전!
# Python으로 set을 쓸 일이 없다보니 문법이 생각 안 나서 검색을 이리저리 했다 ㅠ

def solution(relation):
    answer = list()
    for i in range(1, 1 << len(relation[0])): # 조합 생성
        tmp_set = set()
        for j in range(len(relation)):
            tmp = ''
            for k in range(len(relation[0])):
                if i & (1 << k):
                    tmp += str(relation[j][k])
            tmp_set.add(tmp)
            
        if len(tmp_set) == len(relation):
            able = True
            for num in answer:
                if (num & i) == num:
                    able = False
                    break
            if able:
                answer.append(i)
    return len(answer) 
