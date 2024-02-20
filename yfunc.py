from typing import *
import os
import time
import re
import json as js
import hashlib
import clipboard
import random
from PIL import Image
import math

#------------------------

class ybytes(bytes):

    @staticmethod
    def from_str(s: str, encode='utf-8') -> 'ybytes':
        return ybytes(s.encode(encoding=encode))
    
    def to_str(self, encode='utf-8') -> 'ystr':
        return ystr(self.decode(encoding=encode))

#------------------------

class ystr(str):

    re_pattern_cache: dict = {}
    time_count = 0

    ##-----------------------

    def __add__(self, __val) -> 'ystr':
        return ystr(super().__add__(__val))

    def __getitem__(self, __key) -> 'ystr':
        return ystr(super().__getitem__(__key))
    
    ##-----------------------

    def datetime(self) -> 'datetime':
        return datetime(self)

    def filepath(self) -> 'filepath':
        return filepath(self)

    def java(self) -> 'java':
        return java(self)

    def json(self) -> 'json':
        return json(self)

    def mathematics(self) -> 'mathematics':
        return mathematics(self)

    def number(self) -> 'number':
        return number(self)

    def row(self) -> 'row':
        return row(self)

    def sql(self) -> 'sql':
        return sql(self)

    def text(self) -> 'text':
        return text(self)

    def timestamp(self) -> 'timestamp':
        return timestamp(self)

    def url(self) -> 'url':
        return url(self)

    def variable(self) -> 'variable':
        return variable(self)

    def word(self) -> 'word':
        return word(self)

    ##-----------------------
    
    def count_time(self, flag=None) -> 'ystr':
        t = int(time.time()*1000)
        if flag != None:
            print(f'{flag}: {t-ystr.time_count} ms')
        ystr.time_count = t
        return self

    def print(self) -> 'ystr':
        print('--------------------BEGIN--------------------')
        print(self)
        print('---------------------END---------------------')
        return self

    @staticmethod
    def from_file(path: str, encode='utf-8') -> 'ystr':
        with open(path, 'r', encoding=encode) as f:
            content = f.read()
        return ystr(content)
    
    def to_file(self, path: str, encode='utf-8', force=False) -> 'ystr':
        if not force and not ystr(path).filepath().exist():
            raise Exception('path not exists, use force=True to create path')
        if not os.path.exists(path):
                os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, 'w', encoding=encode) as f:
            f.write(self)
        return self

    @staticmethod
    def from_clipboard() -> 'ystr':
        return ystr(clipboard.paste())

    def to_clipboard(self) -> 'ystr':
        clipboard.copy(self)
        return self

    def appendto_clipboard(self, spacing='') -> 'ystr':
        old = clipboard.paste()
        clipboard.copy(old+spacing+self)
        return self

    def split(self, by: str = None, trim_each=False, remove_null=False) -> list['ystr']:
        return [
                ystr(s.strip() if trim_each else s) 
                for s in super().split(by)
                if not remove_null or s != ''
            ]

    def strip(self, t: str = None) -> 'ystr':
        return ystr(super().strip(t))
    
    def join(self, ss: Iterable[str]) -> 'ystr':
        return ystr(super().join(ss))

    def to_rows(self) -> list['ystr']:
        return self.split('\n', trim_each=True, remove_null=True)
    
    def to_words(self) -> list['ystr']:
        return self.split(trim_each=True, remove_null=True)

    def shrink(self, spacing='') -> 'ystr':
        return ystr(spacing).join(self.to_rows())

    @staticmethod
    def do_re_action_with_cache(action: str, r: str, s: str):
        if r in ystr.re_pattern_cache:
            pt = ystr.re_pattern_cache[r]
        else:
            pt = re.compile(r)
            # print('do complie:' + r)
            ystr.re_pattern_cache[r] = pt
        if action == 'match':
            return pt.match(s)
        if action == 'search':
            return pt.search(s)
        if action == 'findall':
            return pt.findall(s)

    def re_match(self, r: str) -> tuple['ystr', int, int]:
        if r == None:
            return ystr(), -1, -1
        # mt = re.match(r, self)
        mt = ystr.do_re_action_with_cache('match', r, self)
        if mt == None:
            return ystr(), -1, -1
        return ystr(mt.group()), mt.start(), mt.end()

    def re_search(self, r: str) -> tuple['ystr', int, int]:
        if r == None:
            return ystr(), -1, -1
        # mt = re.search(r, self)
        mt = ystr.do_re_action_with_cache('search', r, self)
        if mt == None:
            return ystr(), -1, -1
        return ystr(mt.group()), mt.start(), mt.end()

    def re_findall(self, r: str) -> list['ystr']:
        if r == None:
            return []
        # return [ystr(s) for s in re.findall(r, self)]
        return [ystr(s) for s in ystr.do_re_action_with_cache('findall', r, self)]

    def is_match(self, r: str) -> bool:
        return self.re_match(r)[1] != -1 and self.re_match(r)[0] == self
    
    def any_match(self, *r) -> bool:
        return any(self.is_match(rr) for rr in r)

    def of(self, *s: str, r=None, ignore_case=True) -> bool:
        rs = ylist(s).collect(ystr)
        if ignore_case:
            rs = ['(?i)'+r for r in rs]
        if r != None:
            rs.append(r)
        return self.any_match(*rs)
    
    # 寻找一些模式串t, 返回所有t的位置[l, r)的生成器
    # 如果reverse为True, 则从右往左找, 否则从左往右找
    # 如果两个模式串前后冲突, 则按找的顺序取第一个
    # 如果没有任何模式串, 返回 (-1, -1)
    def finds(self, *t: str, reverse=False) -> Generator[tuple[int, int], None, None]:
        n = len(self)
        k = -1 if reverse else n
        bound = n - k
        exist = False
        while True:
            pos = k, k
            for p in (p for p in t if len(p) > 0):
                cur = self.rfind(p, 0, bound) if reverse else self.find(p, bound)
                if cur == -1:
                    continue
                if (reverse and cur > pos[0]) or (not reverse and cur < pos[0]):
                    pos = cur, cur+len(p)
            if pos[0] == k:
                break
            exist = True
            bound = pos[int(k>=0)]
            yield pos
        if not exist:
            yield -1, -1
    
    # 返回第一个模式串t的位置[l, r)
    # 如果没找到, 返回 (-1, -1)
    def find_first(self, t: str) -> tuple[int, int]:
        return next(self.finds(t))

    # 返回最后一个模式串t的位置[l, r)
    # 如果没找到, 返回 (-1, -1)
    def find_last(self, t: str) -> tuple[int, int]:
        return next(self.finds(t, reverse=True))

    # 返回在第一个after之后, 第一个before之前的第一个l和第一个r之间的子串
    # 如果r为None, 默认等于l
    # 如果reverse为True, 则从右往左找, 否则从左往右找
    # 如果没找到, 返回空串
    def find_around(self, l: str, r: str = None, after: str = None, before: str = None, reverse=False) -> 'ystr':
        poses = self.finds(*ylist([after, before, l, r]).collect(ystr).unique(), reverse=reverse)
        if r == None:
            r = l
        res = ''
        if reverse:
            step = 0 if before != None else 1
            res_x, res_y = -1, -1
            for x, y in poses:
                cur = self[x:y]
                if step == 0 and cur == before:
                    step = 1
                    continue
                if step > 0 and cur == after:
                    break
                if step == 1 and cur == r:
                    res_y = x
                    step = 2
                    continue
                if step == 2 and cur == l:
                    res_x = y
                    break
            res = self[res_x:res_y] if res_x != -1 and res_y != -1 else ''
        else:
            step = 0 if after != None else 1
            res_x, res_y = -1, -1
            for x, y in poses:
                cur = self[x:y]
                if step == 0 and cur == after:
                    step = 1
                    continue
                if step > 0 and cur == before:
                    break
                if step == 1 and cur == l:
                    res_x = y
                    step = 2
                    continue
                if step == 2 and cur == r:
                    res_y = x
                    break
            res = self[res_x:res_y] if res_x != -1 and res_y != -1 else ''
        return ystr(res)

    # 按照括号闭合的原则, 找到每一个l对应的r, 返回它们的起始下标映射(key: l_begin_pos, value: r_begin_pos)
    # 如果reverse为True, 则从右往左找, 否则从左往右找
    def close_find(self, l: str, r: str, reverse=False) -> dict[int, int]:
        res = {}
        l_pos_s = []
        for x, y in self.finds(l, r, reverse=reverse):
            if self[x:y] == l:
                l_pos_s.append(x)
            if self[x:y] == r and len(l_pos_s) > 0:
                res[l_pos_s.pop()] = x
        return res

    # 将位置为pos: [l, r)的一些子串去掉后, 返回剩余的每段子串的生成器
    # 如果keep为True, 则也返回去掉的那些子串, 否则丢弃
    # 如果reverse为True, 则从右往左找, 否则从左往右找
    def mult_cut(self, *pos: tuple[int, int], keep=True, reverse=False) -> Generator['ystr', None, None]:
        if len(self) == 0:
            yield ystr()
            return
        ps = [p for p in pos if p[0] <= p[1]]
        if reverse:
            ps.sort(key=lambda x: x[1], reverse=True)
            poses = [(len(self), len(self))]
            for x, y in ps:
                if y <= poses[-1][0]:
                    poses.append((x, y))
        else:
            ps.sort(key=lambda x: x[0])
            poses = [(-1, -1)]
            for x, y in ps:
                if x >= poses[-1][1]:
                    poses.append((x, y))
        poses = poses[1:]
        if len(poses) == 0:
            yield self
            return
        if reverse:
            if len(t:=self[poses[0][1]:])>0: yield t
            for i in range(len(poses)-1):
                if keep and len(t:=self[poses[i][0]:poses[i][1]])>0: yield t
                if len(t:=self[poses[i+1][1]:poses[i][0]])>0: yield t
            if keep and len(t:=self[poses[-1][0]:poses[-1][1]])>0: yield t
            if len(t:=self[:poses[-1][0]])>0: yield t
        else:
            if len(t:=self[:poses[0][0]])>0: yield t
            for i in range(len(poses)-1):
                if keep and len(t:=self[poses[i][0]:poses[i][1]])>0: yield t
                if len(t:=self[poses[i][1]:poses[i+1][0]])>0: yield t
            if keep and len(t:=self[poses[-1][0]:poses[-1][1]])>0: yield t
            if len(t:=self[poses[-1][1]:])>0: yield t

    # 按一系列模式串t分割, 返回分割后的每段子串的生成器
    # 如果keep为True, 则也返回去掉的那些子串, 否则丢弃
    # 如果reverse为True, 则从右往左找, 否则从左往右找
    def cuts(self, *t: str, keep=True, reverse=False) -> Generator['ystr', None, None]:
        poses = list(self.finds(*t, reverse=reverse))
        return self.mult_cut(*poses, keep=keep, reverse=reverse)
    
    # 将下标为index的一些字符去掉后, 返回剩余的每段子串的生成器
    # 如果keep为True, 则也返回去掉的那些子串, 否则丢弃
    def cut(self, *index: int, keep=True) -> Generator['ystr', None, None]:
        poses = [(i, i+1) for i in index if i >= 0 and i < len(self)]
        return self.mult_cut(*poses, keep=keep)

    def discard(self, *pos: tuple[int, int], reverse=False) -> 'ystr':
        return ystr().join(self.mult_cut(*pos, keep=False, reverse=reverse))

    # 按第一个l和最后一个r分割, 返回三段子串(不保留l和r)
    def lr_split(self, l: str = ' ', r: str = ' ') -> tuple['ystr', 'ystr', 'ystr']:
        x1, y1 = self.find_first(l)
        x2, y2 = self.find_last(r)
        if x1 == -1 and x2 == -1:
            return '', self, ''
        if x1 == -1:
            return '', self[:x2], self[y2:]
        if x2 == -1:
            return self[:x1], self[y1:], ''
        return self[:x1], self[y1:x2], self[y2:]

    # 根据by进行split但忽略brackets中的by
    def close_split(
            self, by: str = ' ', 
            brackets: tuple[tuple[str, str]] = (('(',')'),('[',']'),('<','>'),('{','}'),('"','"'),("'","'"),('`', '`')),
            trim_each: bool = True,
            remove_null: bool = True,
        ) -> Generator['ystr', None, None]:
        parts = self.cuts(by, *ylist(brackets).flatten())
        cur = ''
        balance = [0 for _ in brackets]
        for p in parts:
            if p == by and all(x==0 for x in balance):
                if trim_each:
                    cur = cur.strip()
                if cur != '' or not remove_null:
                    yield ystr(cur)
                cur = ''
                continue
            for i, cl in enumerate(brackets):
                if cl[0] != cl[1]:
                    if p == cl[0]:
                        balance[i] += 1
                    if p == cl[1]:
                        balance[i] -= 1
                else:
                    if p == cl[0]:
                        balance[i] ^= 1
            cur += p
        if all(x==0 for x in balance):
            if trim_each:
                cur = cur.strip()
            if cur != '' or not remove_null:
                yield ystr(cur)       

    def md5(self, encode='utf-8') -> 'ystr':
        return ystr(hashlib.md5(self.encode(encoding=encode)).hexdigest())

class row():
    
    def __init__(self, s: str) -> None:
        self.s = ystr(s)
    
    @staticmethod
    def from_words(*word: str) -> 'ystr':
        return ystr(' '.join(word))

class word():

    def __init__(self, s: str) -> None:
        self.s = ystr(s)

class variable():

    def __init__(self, s: str) -> None:
        self.s = ystr(s)

    def format(self, style: str) -> 'ystr':
        if len(style) < 4:
            return self.s
        def split_to_words(s: ystr) -> list['ystr']:
            if '_' in s:
                return s.split('_')
            ret = []
            cur = ''
            for c in s:
                if c.islower():
                    cur += c
                else:
                    if cur != '':
                        ret.append(cur)
                    cur = c
            if cur != '':
                ret.append(cur)
            return ret
        words = [word.lower() for word in split_to_words(self.s)]
        res_words = []
        first_word = (words[0][0].lower() if style[0].islower() else words[0][0].upper()) + \
            (words[0][1:].lower() if style[1].islower() else words[0][1:].upper())
        res_words.append(first_word)
        for word in words[1:]:
            cur_word = (word[0].lower() if style[2].islower() else word[0].upper()) + \
                (word[1:].lower() if style[3].islower() else word[1:].upper())
            res_words.append(cur_word)
        return (style[4] if len(style) >= 5 else '').join(res_words)

    def aaBb(self) -> 'ystr':
        return self.format('aaBb')

    def AaBb(self) -> 'ystr':
        return self.format('AaBb')

class datetime():

    def __init__(self, s: str) -> None:
        self.s = ystr(s)

    def to_timestamp(self) -> 'ystr':
        if len(self.s) < 12:
            date = time.strptime(self.s, "%Y-%m-%d")
        else:
            date = time.strptime(self.s, "%Y-%m-%d %H:%M:%S")
        return ystr(int(time.mktime(date)))
    
    @staticmethod
    def now() -> 'ystr':
        return ystr().timestamp().now().timestamp().to_datetime()

class timestamp():

    # 13位精度到毫秒; 10位精度到秒
    def __init__(self, s: str, format=False) -> None:
        self.s = ystr(s).number().format(13) if format else ystr(s)

    @staticmethod
    def now() -> 'ystr':
        return ystr(int(time.time()))

    # 精度到秒
    def to_datetime(self, fmt="%Y-%m-%d %H:%M:%S") -> 'ystr':
        t = time.localtime(int(self.s[:10]))
        return ystr(time.strftime(fmt, t))

class filepath():

    def __init__(self, s: str) -> None:
        self.s = ystr(s)

    def search(self, *suffix: str) -> list['ystr']:
        def add_check_suffix(res: list['ystr'], path: 'ystr') -> None:
            if suffix == () or any(path.endswith(suff) for suff in suffix if suff != None):
                res.append(path)
        def dfs_search(p: 'ystr') -> list['ystr']:
            ret = []
            if not os.path.isdir(p):
                add_check_suffix(ret, p)
                return ret
            pathes = os.listdir(p)
            for path in pathes:
                full_path = ystr(os.path.join(p, path))
                if os.path.isdir(full_path):
                    ret += dfs_search(full_path)
                else:
                    add_check_suffix(ret, full_path)
            return ret
        return dfs_search(self.s)
    
    def suffix(self, keep_ext=True) -> 'ystr':
        if keep_ext:
            return self.s.split('/')[-1]
        return '.'.join((self.s.split('/')[-1]).split('.')[:-1])
    
    def ext(self) -> 'ystr':
        if os.path.isdir(self.s):
            return ''
        return (self.s.split('/')[-1]).split('.')[-1]

    def exist(self) -> bool:
        return os.path.exists(self.s)

    def txt(self, encode='utf-8') -> 'TextFileHandler':
        return TextFileHandler(self.s, encode)
        
class TextFileHandler:
    
    def __init__(self, path: str, encode='utf-8') -> None:
        self.path = path
        self.content = ystr().from_file(path, encode=encode)
        self.length = len(self.content)
        self.md5 = self.content.md5()

    def to_json(self) -> 'ystr':
        return ystr().json().from_object(self)    

class java():

    def __init__(self, s: str) -> None:
        self.s = ystr(s)

    def parse(self):
        try:
            return JavaFunc(self.s)
        except:
            try:
                return JavaClass(self.s)
            except:
                raise
        
class JavaFuncPara:

    def __new__(cls, para_raw = None) -> Self:
        self = super().__new__(cls)
        self.type = ''
        self.name = ''
        self.extra = ''
        return self
    
    def __init__(self, para_raw: str = None) -> None:
        if para_raw == None:
            return
        parts = list(ystr(para_raw).strip().close_split())
        self.name = parts[-1].shrink(' ')
        self.type = parts[-2].shrink(' ')
        if len(parts) > 2:
            self.extra = ''.join(parts[:-2])

class JavaFunc:

    def __new__(cls, func_raw: str = None):
        self = super().__new__(cls)
        self.func_name = ''
        self.access_level = ''
        self.return_type = ''
        self.paras: list[JavaFuncPara] = []
        self.throw = ''
        self.body = ''
        self.extra = ''
        return self

    def __init__(self, func_raw: str = None) -> None:
        if func_raw == None:
            return
        func_raw = ystr(func_raw)
        _, x, _ = func_raw.re_search(r'(public|private|protect)')
        self.extra = func_raw[:x]
        func_head, self.body, _ = func_raw[x:].strip().lr_split('{', '}')
        head_prefix, head_paras, self.throw = func_head.strip().lr_split('(', ')')
        self.access_level, self.return_type, self.func_name = head_prefix.strip().lr_split()
        self.paras = [JavaFuncPara(p) for p in head_paras.strip().close_split(',')]

class JavaField:

    def __new__(cls, field_raw: str = None) -> Self:
        self = super().__new__(cls)
        self.name = ''
        self.type = ''
        self.access_level = ''
        self.comment = ''
        self.extra = ''
        return self

    def __init__(self, field_raw: str = None) -> None:
        if field_raw == None:
            return
        field_raw = ystr(field_raw).shrink()
        fd, l1, r1 = field_raw.re_search(r'(private|public|protect)[\w\W]*;')
        cm, l2, r2 = field_raw.re_search(r'/\*[\w\W]*\*/')
        self.extra = field_raw.discard((l1, r1), (l2, r2))
        self.comment = cm.strip('/*').strip()
        pos__type = 0
        skip_words = ('public', 'private', 'protect', 'static', 'final')
        fws = fd.strip(' ;').to_words()
        for i, w in enumerate(fws):
            if not w.of(*skip_words):
                pos__type = i
                break
        self.type = fws[pos__type]
        self.name = fws[pos__type+1]
        self.access_level = fws[0]
        
class JavaClass:

    def __new__(cls, java_raw: str) -> Self:
        self = super().__new__(cls)
        self.class_name = ''
        self.package = ''
        self.imports: list[ystr] = []
        self.fields: list[JavaField] = []
        self.functions: list[JavaFunc] = []
        return self
    
    def __init__(self, java_raw: str) -> None:
        self.imports: list[ystr] = []
        self.fields: list[JavaField] = []
        self.functions: list[JavaFunc] = []
        flag = True
        cache = ystr()
        for row in ystr(java_raw).to_rows():
            if row.startswith('package '):
                self.package = row.find_around(l=' ', r=';', after='package')
            if row.startswith('import '):
                self.imports.append(row.find_around(l=' ', r=';', after='import'))
            if row.startswith('public class '):
                self.class_name = row.find_around(l=' ', after='class')
                flag = False
                continue
            if flag:
                continue
            cache += row
            if self.content_field(cache):
                self.fields.append(JavaField(cache))
                cache = ystr()
            if self.content_func(cache):
                self.functions.append(JavaFunc(cache))
                cache = ystr()

    def content_field(self, cache: ystr) -> bool:
        return cache.shrink().is_match(r'[\w\W]*(private|public|protect)[^{}]*;')
    
    def content_func(self, cache: ystr) -> bool:
        if not cache.shrink().is_match(r'[\w\W]*(private|public|protect)[\w\W]*{[\w\W]*}'):
            return False
        pos, _ = cache.find_first('{')
        return pos in cache.close_find('{', '}').keys()

class json():

    def __init__(self, s: str) -> None:
        self.s = ystr(s)

    def format(self, indent=4) -> 'ystr':
        return ystr(js.dumps(
                        js.loads(self.s), 
                        ensure_ascii = False, 
                        indent = indent,
                        default = lambda obj: obj.__dict__,
                    )
                )   
    
    @staticmethod
    def from_object(obj, indent=4) -> 'ystr':
        return ystr(js.dumps(
                        obj, 
                        ensure_ascii = False, 
                        indent = indent,
                        default = lambda obj: obj.__dict__,
                    )
                )

    def to_dic(self) -> 'ydic':
        return ydic(js.loads(self.s))

class number():

    def __init__(self, s: str) -> None:
        self.s = ystr(s)

    def format(self, length, fill='0') -> 'ystr':
        if len(self.s) > length:
            return (self.s[-length:])
        return ystr(fill*(length-len(self.s))+self.s)

class mathematics():

    def __init__(self, s: str) -> None:
        self.s = ystr(s)

class sql():

    def __init__(self, s: str) -> None:
        self.s = ystr(s)

    @staticmethod
    def gen_in(*word: str, row_count=0, add_quotes=False) -> 'ystr':
        words = ["'" + w + "'" for w in word] if add_quotes else word
        try:
            row_count = int(row_count)
        except:
            row_count = 0
        if row_count < 1:
            fra = ','.join(words)
            res = f'in ({fra})'
        else:
            fra = ''
            for i, w in enumerate(words):
                fra += f'{w},\n' if (i+1) % row_count == 0 else f'{w},'
            fra = fra.strip()[:-1]
            res = 'in (\n' + ystr(fra).text().add_tab() + '\n)'
        return ystr(res)

    def parse(self):
        return Table(self.s)

class Col:

    def __init__(self) -> None:
        self.name = ''
        self.type = ''
        self.comment = ''
        self.can_null = True
        self.default = ''
    
class Table:

    def __new__(cls, sql: str):
        self = super().__new__(cls)
        self.table_name = ''
        self.cols = []
        self.keys = []
        self.extra = ''
        return self

    def __init__(self, sql: str) -> None:
        sql = ystr(sql)
        x, _ = sql.find_first('(')
        y, _ = sql.find_last(')')
        if x == -1 or y == -1:
            raise 
        part1 = sql[:x]
        part2 = sql[x+1:y]
        part3 = sql[y+1:]
        pw1 = ystr(part1).to_words()
        if not ystr('create').of(*pw1):
            raise 
        for i, w in enumerate(pw1):
            if w.of('table'):
                break
        self.table_name = pw1[i+1].strip(" ;`'")
        self.cols: list[Col] = []
        self.keys = []
        pr2 = part2.close_split(',', remove_null=True, trim_each=True)
        for r in pr2:
            try:
                pw2 = list(r.close_split())
                if ystr('key').of(*pw2):
                    self.keys.append(r)
                    continue
                t = Col()
                t.name = pw2[0].strip(" ;`'")
                t.type = pw2[1].strip(" ;`'")
                for i, w in enumerate(pw2):
                    if i+1 >= len(pw2):
                        break
                    if w.of('not') and pw2[i+1].of('null'):
                        t.can_null = False
                    if w.of('comment'):
                        t.comment = pw2[i+1].strip(" ;`'")
                    if w.of('default'):
                        t.default = pw2[i+1].strip(" ;`'")
                self.cols.append(t)
            except Exception as e:
                e.add_note(f'at:[{r}]')
                raise
        self.extra = part3.strip(' ;')

class text():

    def __init__(self, s: str) -> None:
        self.s = ystr(s)
    
    @staticmethod
    def from_rows(*row: 'ystr') -> 'ystr':
        return ystr('\n'.join(row))
    
    def add_tab(self) -> 'ystr':
        poses = [p[0] for p in self.s.finds('\n')]
        res = '    ' + self.s[:poses[-1]].replace('\n', '\n    ') + \
            (t if (t:=self.s[poses[-1]:]).strip()=='' else t.replace('\n', '\n    '))
        return ystr(res)

class url():

    def __init__(self, s: str) -> None:
        self.s = ystr(s)

#------------------------

class ylist(list):

    def __add__(self, __val) -> 'ylist':
        return ylist(super().__add__(__val))
    
    ##-----------------------

    @staticmethod
    def from_str(s: str, encode='utf-8') -> 'ylist':
        return ylist(ybytes.from_str(s, encode=encode))
    
    def to_str(self, encode='utf-8') -> 'ystr':
        return ybytes(self).to_str(encode=encode)

    def print(self) -> 'ylist':
        print('--------------------BEGIN--------------------')
        print(self)
        print('---------------------END---------------------')
        return self

    def append(self, obj) -> 'ylist':
        super().append(obj)
        return self

    def unique(self) -> 'ylist':
        ret = []
        st = set()
        for x in self:
            if x not in st:
                ret.append(x)
                st.add(x)
        return ret
    
    def group(self, size: int = 0) -> 'ylist':
        if size <= 0:
            return self
        res = ylist()
        sub = ylist()
        cnt = 0
        for o in self:
            if cnt == size:
                res.append(sub)
                sub = ylist()
                cnt = 0
            sub.append(o)
            cnt += 1
        if len(sub) > 0:
            res.append(sub)
        return res

    def flatten(self):
        def dfs_flatten(obj) -> 'ylist':
            res = ylist()
            if type(obj) in (list, ylist, tuple):
                for o in obj:
                    res += dfs_flatten(o)
            else:
                res.append(obj)
            return res
        return dfs_flatten(self)
    
    def collect(self, *target_type) -> 'ylist':
        res = ylist()
        for x in self:
            for t in target_type:
                try:
                    res.append(t(x))
                    break
                except:
                    pass
        return res
    
    def filter(self, *target_type) -> 'ylist':
        res = ylist()
        for x in self:
            if type(x) in target_type:
                res.append(x)
        return res

    @staticmethod
    def random(len, l, r) -> 'ylist':
        return ylist(random.randint(l, r) for _ in range(len))

    def to_dic(self) -> 'ydic':
        res = ydic()
        for i, x in enumerate(self):
            res[i] = x
        return res

    ##------------------------

    def trans(self) -> 'Trans':
        return Trans(self)

class Trans:

    def __init__(self, l: list) -> None:
        self.l = ylist(l)
        
    def finish(self) -> 'ylist':
        return self.l

    def do_mapping(self, mapper: dict) -> 'Trans':
        self.l = ylist(mapper[x] if x in mapper else x for x in self.l)
        return self

    def mapping__fibo(self, k0, k1, k2, reverse=False) -> 'Trans':
        def fibo_random(k0, k1, k2) -> 'ylist':
            pri = [
                32, 101, 114, 116, 115, 97, 110, 
                10, 105, 111, 102, 108, 95, 112, 
                100, 39, 99, 40, 41, 61, 46, 
                117, 109, 58, 119, 44, 91, 93, 
                98, 121, 118, 103, 49, 104, 45, 
                62, 123, 48, 125, 34, 43, 47,
            ]
            res = []
            cnt = 0
            while len(res) < k0:
                cnt += 1
                cur = (k1+k2) % k0
                if cur not in res and cnt >= 12:
                    res.append(cur)
                k1, k2 = k2, cur
            res = [x for x in res if x < 256]
            pr_cnt = len(pri)
            pr = [x for x in res if x >= 1 and x <= pr_cnt]
            def force_mapping(a, b):
                tmp = res[a]
                pos_b = res.index(b)
                res[a] = b
                res[pos_b] = tmp
            force_mapping_list = [(0, 0), (255, 255)]
            for i in range(pr_cnt):
                force_mapping_list.append((pri[i], pr[i]))
            for a, b in force_mapping_list:
                force_mapping(a, b)
            if len(res) != 256:
                raise
            for i in range(256):
                if i not in res:
                    raise
            return ylist(res)
        mapper = fibo_random(k0, k1, k2).to_dic()
        if reverse:
            mapper = mapper.reverse()
        return self.do_mapping(mapper)

#------------------------   

class ydic(dict):

    def gevert(self, key, convert_type=None, default=None):
        ret = self.get(key, default)
        if convert_type != None:
            try:
                return convert_type(ret)
            except:
                return default
        return ret            

    def reverse(self, join=False) -> 'ydic':
        res = ydic()
        for k, v in self.items():
            if v not in res:
                res[v] = k
                continue
            if not join:
                raise
            if type(res[v]) == ylist:
                res[v].append(k)
            else:
                res[v] = ylist([res[v], k])
        return res

#------------------------

class ypic():

    def __init__(self, p: Image.Image) -> None:
        self.p = p
    
    @staticmethod
    def empty_pic(w: int, h: int) -> 'ypic':
        return ypic(Image.new('RGB', (w, h)))

    @staticmethod
    def from_file(path: str) -> 'ypic':
        return ypic(Image.open(path).convert('RGB'))
    
    def to_file(self, path: str = None) -> 'ypic':
        if path == None:
            path = f'{ystr().timestamp().now()}.png'
        self.p.save(path)
    
    def set_pixel(self, pos: tuple[int, int], value: int, chn: int) -> 'ypic':
        data = list(self.p.getpixel(pos))
        data[chn] = value
        self.p.putpixel(pos, tuple(data))
        return self
    
    # pp: (pos, channel, value)
    def load_pps(self, pp_list: list[tuple[int, int, int]]) -> 'ypic':
        if len(pp_list) == 0:
            return self
        w, h = self.p.size
        pp_need = pp_list[-1][0] + 1
        print(f'image size = {w}x{h}, pp count = {w*h}, pp need = {pp_need} ({(pp_need)/(w*h)*100}%)')
        if w*h < pp_need:
            raise Exception(f'image too small, which pp count = {w*h} but need {pp_need}')
        for p, t, d in pp_list:
            x = p % w
            y = p // w
            self.set_pixel((x, y), d, t)
        return self
    
    def load_str(self, s: str, k0=None, k1=None, k2=None, shift=100, head_len=10) -> 'ypic':
        def gen_pixel_point(data: list) -> list:
            if data == None or len(data) == 0:
                return []
            res = [(0, 0, 0)]
            for i, d in enumerate(data):
                nxt_p, nxt_t = ypic.__get_next__(res[i], shift)
                res.append((nxt_p, nxt_t, d))
            return res[1:]
        data = ylist.from_str(s)
        str__len = ystr(len(data))
        if len(str__len) > head_len:
            raise Exception(f'head len too long which reach {len(str__len)}')
        data = ylist(int(x) for x in str__len.number().format(head_len)) + data
        if k0 != None:
            data = data.trans().mapping__fibo(k0, k1, k2).finish()
        self.load_pps(gen_pixel_point(data))
        return self
    
    def fetch_str(self, k0=None, k1=None, k2=None, shift=100, head_len=10) -> 'ystr':
        pp_data = list(self.p.getdata())
        pps = [(0, 0, 0)]
        while True:
            nxt_p, nxt_t = ypic.__get_next__(pps[-1], shift)
            if nxt_p >= len(pp_data):
                break
            pps.append((nxt_p, nxt_t, pp_data[nxt_p][nxt_t]))
        data = ylist(pp[2] for pp in pps[1:])
        if k0 != None:
            data = data.trans().mapping__fibo(k0, k1, k2, reverse=True).finish()
        body_len = int(ystr().join(ystr(x) for x in data[:head_len]))
        data = data[head_len:head_len+body_len]
        return ylist(data).to_str()
    
    def load_files(self, *filepath: str, k0=None, k1=None, k2=None, shift=100, head_len=10) -> 'ypic':
        all_content = {
            'files': []
        }
        all_content_len = 0
        for f in filepath:
            content = ystr().from_file(f)
            all_content['files'].append({
                'content': content,
                'filepath': f,
                'md5': content.md5(),
            })
            all_content_len += len(content)
        all_content['md5'] = ystr().json().from_object(all_content['files']).md5()
        self.load_str(
            ystr().json().from_object(all_content),
            k0 = k0,
            k1 = k1,
            k2 = k2,
            shift = shift,
            head_len = head_len,
        )
        print(f'load {all_content_len} chars')
        return self

    def fetch_files(self, res_dic: str, k0=None, k1=None, k2=None, shift=100, head_len=10) -> 'ypic':
        all_content = ystr(self.fetch_str(
            k0 = k0,
            k1 = k1,
            k2 = k2,
            shift = shift,
            head_len = head_len,
        )).json().to_dic()
        if all_content['md5'] != ystr().json().from_object(all_content['files']).md5():
            print('warn - md5 check not ok: overall')
        print('fetching files:')
        for i, f in enumerate(all_content['files']):
            content = ystr(f['content'])
            file_path = f['filepath']
            if f['md5'] != content.md5():
                print(f'warn - md5 check not ok: {file_path}')
            else:
                print(f'    {i+1}.{file_path} ({len(content)} chars)')
            content.to_file(os.path.join(res_dic, file_path), force=True)
        return self

    def __get_next__(pp: tuple, shift) -> tuple:    
        p, c, d = pp
        shift = c + d%9 + 1 + shift
        p += shift // 3
        c = shift % 3
        return p, c




