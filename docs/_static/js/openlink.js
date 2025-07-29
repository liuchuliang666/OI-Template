document.addEventListener("DOMContentLoaded", function () {
    const currentHost = window.location.hostname;

    const processLinks = (root) => {
        root.querySelectorAll('a[href^="http"]').forEach(link => {
            try {
                const linkUrl = new URL(link.href);
                if (linkUrl.hostname !== currentHost && !link.target) {
                    link.target = '_blank';
                    link.rel = 'noopener noreferrer';
                }
            } catch (e) { }
        });
    };

    // 初始化扫描
    processLinks(document.body);

    // 监听动态内容
    const observer = new MutationObserver(mutations => {
        mutations.forEach(mutation => {
            mutation.addedNodes.forEach(node => {
                if (node.nodeType === 1) processLinks(node);
            });
        });
    });

    observer.observe(document.body, {
        childList: true,
        subtree: true
    });
});