import re

def on_post_page(output, page, config, **kwargs):
    """
    智能添加公式空格：如果公式一侧有中文标点，则该侧不添加空格
    """
    # 中文标点集合（正则表达式字符类）
    cjk_punctuation = r'！？，。、；“”‘’（）【】《》—…#￥'

    # 匹配行内公式标签
    pattern = re.compile(
        r'(?P<left>[\s' + cjk_punctuation + r']*)'  # 公式左侧内容（可能包含中文标点或空格）
        r'(?P<katex><span class="arithmatex">.*?</span>)'  # 公式标签
        r'(?P<right>[\s' + cjk_punctuation + r']*)'  # 公式右侧内容
    )

    def replace(match):
        left = match.group('left')
        katex = match.group('katex')
        right = match.group('right')

        # 左侧是否需要加空格？如果左侧无中文标点且不是行首，则加
        new_left = ' ' if not re.search(r'[' + cjk_punctuation + r']$', left) else ''

        # 右侧是否需要加空格？如果右侧无中文标点且不是行尾，则加
        new_right = ' ' if not re.search(r'^[' + cjk_punctuation + r']', right) else ''

        # 合并结果（避免重复添加）
        return left + new_left + katex + new_right + right

    return pattern.sub(replace, output)