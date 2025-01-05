def data_types():
    int_num = 1
    string = 'abc'
    float_num = 123.456
    bool_var = True
    l = [1, 'dfnv']
    d = dict(key='key1', value='value1')
    t = tuple(l)
    s = set(l)
    print(
        [type(int_num).__name__, type(string).__name__, type(float_num).__name__, type(bool_var).__name__,
         type(l).__name__, type(d).__name__, type(t).__name__, type(s).__name__])


if __name__ == "__main__":
    data_types()
