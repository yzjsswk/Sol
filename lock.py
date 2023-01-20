from PIL import Image
import math

def E(s):
  return list(s.encode('utf-8'))

def D(l):
  return bytes(l).decode('utf-8')

def set_pixel(image, pos, target, rgb):
  data = list(image.getpixel(pos))
  data[rgb] = target
  image.putpixel(pos, tuple(data))

class pixel_point:
  def __init__(self, x, y, t, v):
    self.x = x
    self.y = y
    self.t = t
    self.v = v


def gen_pixel_point(data):
  if data == None or len(data) == 0:
      return []
  res = [(0, 0, 0)]
  for i, d in enumerate(data):
      nxt_p, nxt_t = get_next(res[i])
      res.append((nxt_p, nxt_t, d))
  return res[1:]
      
      
def get_next(pp):    
  p, t, d = pp
  shift = t + d%9 + 1
  p += shift // 3
  t = shift % 3
  return p, t


def E_pp(pp_list, image):
  if len(pp_list) == 0:
    return image
  w, h = image.size
  pp_need = pp_list[-1][0] + 1
  if w*h < pp_need:
    raise Exception(f'image too small, which pp count = {w*h} but need {pp_need}')
  for p, t, d in pp_list:
    x = p % w
    y = p // w
    set_pixel(image, (x, y), d, t)
  return image
    
def E_pic(data, size=None):
  pp_list = gen_pixel_point(data)
  pp_need = pp_list[-1][0] + 1
  if size == None:
    w = int(math.sqrt(pp_need)) + 1
    size = (w, w)
  image = Image.new('RGB', size)
  return E_pp(pp_list, image)
  
def E_pic_ima(data, image):
  pp_list = gen_pixel_point(data)
  return E_pp(pp_list, image)

def D_pic(image):
  pp_data = list(image.getdata())
  pp_list = [(0, 0, 0)]
  while True:
    nxt_p, nxt_t = get_next(pp_list[-1])
    if nxt_p >= len(pp_data):
      break
    pp_list.append((nxt_p, nxt_t, pp_data[nxt_p][nxt_t]))
  return [pp[2] for pp in pp_list[1:]]
  
def test_E(content_path):
  with open(content_path, 'r') as f:
    data = E(f.read())
  target_ima = Image.open('charge_item.png')
  pic = E_pic_ima(data, target_ima)
  print(pic.size)
  pic.show()
  pic.save('lock.png')
   
def test_D(png_path):
  ima = Image.open(png_path)
  data = D_pic(ima)
  print(data[:100])
  print(D(data[:1207]))



#test_E('sol.py')
test_D('lock.png')
  