from functools import reduce

def gen_bin_vector_3():
    result = []
    for x1 in range(0,2):
        for x2 in range(0,2):
            for x3 in range(0,2):
                result.append(
                    [
                        reduce(lambda el1,el2: str(el1)+str(el2),[x1,x2,x3])
                    ]
                )
    return result

def gen_bin_vector_4():
    result = []
    for x1 in range(0,2):
        for x2 in range(0,2):
            for x3 in range(0,2):
                for x4 in range(0,2):
                        result.append(
                            [
                                reduce(lambda el1,el2: str(el1)+str(el2),[x1,x2,x3,x4])
                            ]
                        )
    return result

def gen_bin_vector_5():
    result = []
    for x1 in range(0,2):
        for x2 in range(0,2):
            for x3 in range(0,2):
                for x4 in range(0,2):
                    for x5 in range(0,2):
                        result.append(
                            [
                                reduce(lambda el1,el2: str(el1)+str(el2),[x1,x2,x3,x4,x5])
                            ]
                        )
    return result

if __name__ == "__main__":
    print(gen_bin_vector_5())