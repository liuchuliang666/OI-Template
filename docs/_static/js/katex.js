// docs/js/katex-math.js
(function() {
  'use strict';

  // 核心渲染函数（强制行内公式使用 displaystyle）
  function renderKatex() {
    Array.from(document.querySelectorAll('.arithmatex')).forEach(element => {
      const rawTex = element.textContent;
      let tex = rawTex;
      let displayMode = false;

      // 判断块级公式（保留原始逻辑）
      if (tex.startsWith('\\[') && tex.endsWith('\\]')) {
        displayMode = true;
        tex = tex.slice(2, -2);  // 移除 \\[ 和 \\]
      }
      // 处理行内公式（强制添加 displaystyle）
      else if (tex.startsWith('\\(') && tex.endsWith('\\)')) {
        tex = tex.slice(2, -2);  // 移除 \\( 和 \\)
        if (!tex.startsWith('\\displaystyle')) {
          tex = '\\displaystyle ' + tex;  // 自动添加 displaystyle
        }
      } else {
        return; // 跳过不符合格式的内容
      }

      try {
        katex.render(tex, element, {
          displayMode: displayMode,
          throwOnError: false
        });
      } catch (e) {
        console.error('KaTeX 渲染失败:', e);
      }
    });
  }

  // 初始渲染和动态加载逻辑（保持原样）
  if (document.readyState === 'complete') {
    renderKatex();
  } else {
    document.addEventListener('DOMContentLoaded', renderKatex);
  }

  if (typeof app !== 'undefined' && app.dialog) {
    app.dialog.on('loaded', renderKatex);
  }

  const observer = new MutationObserver(mutations => {
    mutations.forEach(mutation => {
      if (mutation.addedNodes.length) {
        renderKatex();
      }
    });
  });

  observer.observe(document.body, {
    childList: true,
    subtree: true
  });
})();