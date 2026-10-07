// ============================================
// DASPRO TASK TRACKER — Interactive JavaScript
// ============================================

if (!window.__DASPRO_INITIALIZED__) {
    window.__DASPRO_INITIALIZED__ = true;

    function runInit() {
        initParticles();
        initThemeToggle();
        initCountUp();
        initProgressBar();
        initSearch();
        initFilterPills();
        initKeyboardShortcuts();
        initScrollReveal();
    }

    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', runInit);
    } else {
        runInit();
    }
}


// === Floating Particles ===
function initParticles() {
    const container = document.getElementById('particles');
    const count = 25;

    for (let i = 0; i < count; i++) {
        const particle = document.createElement('div');
        particle.classList.add('particle');
        particle.style.left = Math.random() * 100 + '%';
        particle.style.animationDuration = (8 + Math.random() * 15) + 's';
        particle.style.animationDelay = (Math.random() * 10) + 's';
        particle.style.width = (2 + Math.random() * 3) + 'px';
        particle.style.height = particle.style.width;
        particle.style.opacity = 0.1 + Math.random() * 0.4;
        container.appendChild(particle);
    }
}

// === Theme Toggle ===
function initThemeToggle() {
    const toggle = document.getElementById('themeToggle');
    const saved = localStorage.getItem('daspro-theme');

    if (saved) {
        document.documentElement.setAttribute('data-theme', saved);
    }

    toggle.addEventListener('click', () => {
        const current = document.documentElement.getAttribute('data-theme');
        const next = current === 'light' ? 'dark' : 'light';
        document.documentElement.setAttribute('data-theme', next);
        localStorage.setItem('daspro-theme', next);

        // Micro animation
        toggle.style.transform = 'rotate(360deg) scale(0.8)';
        setTimeout(() => {
            toggle.style.transform = '';
        }, 300);
    });
}

// === Count Up Animation ===
function initCountUp() {
    const numbers = document.querySelectorAll('.stat-number');
    const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                const el = entry.target;
                const target = parseInt(el.dataset.target);
                animateCount(el, 0, target, 1500);
                observer.unobserve(el);
            }
        });
    }, { threshold: 0.3 });

    numbers.forEach(num => observer.observe(num));
}

function animateCount(el, start, end, duration) {
    const startTime = performance.now();
    const easeOutQuart = t => 1 - Math.pow(1 - t, 4);

    function update(currentTime) {
        const elapsed = currentTime - startTime;
        const progress = Math.min(elapsed / duration, 1);
        const easedProgress = easeOutQuart(progress);
        const current = Math.round(start + (end - start) * easedProgress);

        el.textContent = current.toLocaleString('id-ID');

        if (progress < 1) {
            requestAnimationFrame(update);
        }
    }

    requestAnimationFrame(update);
}

// === Overall Progress Bar ===
function initProgressBar() {
    const allDetails = document.querySelectorAll('.detail-item');
    const doneDetails = document.querySelectorAll('.detail-item.done');
    const total = allDetails.length;
    const completed = doneDetails.length;
    const percent = total > 0 ? Math.round((completed / total) * 100) : 0;

    // Update DOM
    document.getElementById('completedCount').textContent = completed;
    document.getElementById('totalCount').textContent = total;

    // Animate after a brief delay
    setTimeout(() => {
        const bar = document.getElementById('overallProgress');
        bar.style.width = percent + '%';

        // Animate percentage number
        const percentEl = document.getElementById('overallPercent');
        animateCount(percentEl, 0, percent, 2000);
        // Append % after animation
        setTimeout(() => {
            percentEl.textContent = percent + '%';
        }, 2100);
    }, 500);
}

// === Toggle Card Expand ===
function toggleExpand(btn) {
    const details = btn.nextElementSibling;
    const isExpanded = details.classList.contains('expanded');

    // Close all other expanded cards
    document.querySelectorAll('.card-details.expanded').forEach(d => {
        if (d !== details) {
            d.classList.remove('expanded');
            d.previousElementSibling.classList.remove('active');
            d.previousElementSibling.querySelector('span').textContent = 'Lihat Detail';
        }
    });

    if (isExpanded) {
        details.classList.remove('expanded');
        btn.classList.remove('active');
        btn.querySelector('span').textContent = 'Lihat Detail';
    } else {
        details.classList.add('expanded');
        btn.classList.add('active');
        btn.querySelector('span').textContent = 'Tutup Detail';

        // Smooth scroll into view
        setTimeout(() => {
            details.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
        }, 100);
    }
}

// === Search ===
function initSearch() {
    const input = document.getElementById('searchInput');

    input.addEventListener('input', () => {
        const query = input.value.toLowerCase().trim();
        const cards = document.querySelectorAll('.task-card');

        cards.forEach(card => {
            const title = card.querySelector('.card-title').textContent.toLowerCase();
            const topic = card.querySelector('.card-topic').textContent.toLowerCase();
            const details = card.querySelectorAll('.detail-title');
            let detailMatch = false;
            details.forEach(d => {
                if (d.textContent.toLowerCase().includes(query)) detailMatch = true;
            });

            if (title.includes(query) || topic.includes(query) || detailMatch || query === '') {
                card.classList.remove('hidden');
                card.style.opacity = '1';
                card.style.transform = 'translateY(0)';
            } else {
                card.classList.add('hidden');
            }
        });
    });
}

// === Filter Pills ===
function initFilterPills() {
    const pills = document.querySelectorAll('.pill');

    pills.forEach(pill => {
        pill.addEventListener('click', () => {
            // Update active state
            pills.forEach(p => p.classList.remove('active'));
            pill.classList.add('active');

            const filter = pill.dataset.filter;
            const cards = document.querySelectorAll('.task-card');

            cards.forEach(card => {
                const status = card.dataset.status;

                if (filter === 'all') {
                    card.classList.remove('hidden');
                } else if (status === filter) {
                    card.classList.remove('hidden');
                } else {
                    card.classList.add('hidden');
                }
            });

            // Ripple effect on pill
            pill.style.transform = 'scale(0.95)';
            setTimeout(() => {
                pill.style.transform = '';
            }, 150);
        });
    });
}

// === Keyboard Shortcuts ===
function initKeyboardShortcuts() {
    document.addEventListener('keydown', (e) => {
        // Ctrl+K to focus search
        if ((e.ctrlKey || e.metaKey) && e.key === 'k') {
            e.preventDefault();
            const input = document.getElementById('searchInput');
            input.focus();
            input.select();
        }

        // Escape to clear search
        if (e.key === 'Escape') {
            const input = document.getElementById('searchInput');
            if (document.activeElement === input) {
                input.value = '';
                input.dispatchEvent(new Event('input'));
                input.blur();
            }
        }
    });
}

// === Scroll Reveal ===
function initScrollReveal() {
    const revealElements = document.querySelectorAll(
        '.stat-card, .progress-section, .task-card, .timeline-item'
    );

    const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
            if (entry.isIntersecting) {
                entry.target.classList.add('visible');
                observer.unobserve(entry.target);
            }
        });
    }, {
        threshold: 0.1,
        rootMargin: '0px 0px -30px 0px'
    });

    revealElements.forEach(el => {
        el.classList.add('reveal');
        observer.observe(el);
    });

    // Immediately show stats that are likely in viewport
    setTimeout(() => {
        document.querySelectorAll('.stat-card').forEach(card => {
            card.classList.add('visible');
        });
    }, 100);
}

// Make toggleExpand globally available
window.toggleExpand = toggleExpand;
