# https://programmers.co.kr/learn/courses/30/lessons/17686
# 문자열이라 그냥 바로 파이썬으로 풀었다.. ^^.. 이제 문자열은 파이썬 아니면 풀 수 없을 지경ㅋ
# 입력 문자열에서 일단 tail은 순서에 아무 영향을 안 끼치기 때문에 head와 number만 나눴고,
# head와 number가 같으면 들어온 순서에 따라 정렬되기 때문에 h, n와 같이 들어온 인덱스를 저장
# (head, number, index)를 담은 tmp 배열을 sort()하면 알아서 문자열-숫자-인덱스 순으로 정렬되고,
# 마지막에 tmp 배열의 인덱스 값만 받아서 answer 배열에 추가해주면 끝~.~

def solution(files):
    answer = []
    tmp = []
    idx = 0
    for file in files:
        h, n = ("", "") # header, number
        j = 0
        for j in range(0, len(file)):
            if '0' <= file[j] <= '9':
                h = file[0 : j]
                break
        k = 0
        for k in range(j, len(file) + 1):
            if k == len(file):  # tail이 없을 때도 있는데
                n = file[j : k] # 이 부분 오류처리를 안해줘서
                break           # 처음에 런타임 에러 났음 ㅠ
            if not '0' <= file[k] <= '9':
                n = file[j : k]
                break
        tmp.append((h.lower(), int(n), idx))    # case-insensitive
        idx += 1
    tmp.sort()  # 문자열-숫자-인덱스 순으로 정렬
    for t in tmp:
        answer.append(files[t[2]])
    return answer
