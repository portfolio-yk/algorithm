x = [1, 2]
w = [1, 1000]

thred = 1e-12

m_x = 0

def set_pos(m_x, x, total_F):
    for p in x:
        if total_F > 0:
            if m_x < p:
                return (p - m_x) / 2 
        elif total_F < 0:
            if m_x > p:
                return (p - m_x) / 2 
def F(m, d):
    return m / (d * d)

total_F = 0

while True:

    for i in range(len(x)):
        cur_x = x[i]
        cur_w = w[i]
        if cur_x - m_x > thred:
            total_F += F(cur_w ,cur_x - m_x)
    
    #print(total_F)
    
    
    if total_F == 0:
        break

    
    m_x += set_pos(m_x, x, total_F)

    
    print(m_x)
    #break
    total_F = 0


print(m_x)