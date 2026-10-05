/**
 * DASPRO Activity & Assignment Hub - Application Controller
 * Mahasiswa: Muhammad Fajri Setyawan (A11.2026.16638) - UDINUS
 */

(function () {
    'use strict';

    // Application State
    const state = {
        assignments: window.DASPRO_ASSIGNMENTS || [],
        stats: window.DASPRO_STATS || {},
        pdfs: window.DASPRO_PDFS || [],
        currentView: 'explorer', // 'explorer' | 'review' | 'pdf' | 'analytics'
        activeModuleFilter: 'all',
        activeFileTypeFilter: 'all',
        searchQuery: '',
        sortBy: 'default',
        reviewStatusFilter: 'all',
        activeModalTab: 'code',
        currentOpenTask: null,
        reviews: JSON.parse(localStorage.getItem('daspro_reviews_A11_2026_16638') || '{}'),
        theme: localStorage.getItem('daspro_theme') || 'dark'
    };

    // DOM Elements
    const elements = {
        themeToggleBtn: document.getElementById('themeToggleBtn'),
        nimCopyBadge: document.getElementById('nimCopyBadge'),
        navSearchTrigger: document.getElementById('navSearchTrigger'),
        searchInput: document.getElementById('searchInput'),
        searchClearBtn: document.getElementById('searchClearBtn'),
        moduleFilterSelect: document.getElementById('moduleFilterSelect'),
        fileTypeSelect: document.getElementById('fileTypeSelect'),
        sortSelect: document.getElementById('sortSelect'),
        reviewFilterSelect: document.getElementById('reviewFilterSelect'),
        modulePillsContainer: document.getElementById('modulePillsContainer'),
        assignmentGrid: document.getElementById('assignmentGrid'),
        assignmentCountLabel: document.getElementById('assignmentCountLabel'),
        
        // Views
        viewTabs: document.querySelectorAll('.view-tab-btn'),
        viewExplorer: document.getElementById('viewExplorer'),
        viewReview: document.getElementById('viewReview'),
        viewPdf: document.getElementById('viewPdf'),
        viewAnalytics: document.getElementById('viewAnalytics'),
        
        // Review Center
        reviewProgressBarFill: document.getElementById('reviewProgressBarFill'),
        reviewProgressPctLabel: document.getElementById('reviewProgressPctLabel'),
        reviewProgressCountLabel: document.getElementById('reviewProgressCountLabel'),
        reviewTableBody: document.getElementById('reviewTableBody'),
        markAllReviewedBtn: document.getElementById('markAllReviewedBtn'),
        resetReviewBtn: document.getElementById('resetReviewBtn'),
        exportReviewBtn: document.getElementById('exportReviewBtn'),

        // PDF Catalog
        pdfGrid: document.getElementById('pdfGrid'),

        // Analytics
        moduleAnalyticsContainer: document.getElementById('moduleAnalyticsContainer'),
        conceptCloudContainer: document.getElementById('conceptCloudContainer'),

        // Modal
        taskModal: document.getElementById('taskModal'),
        modalCloseBtn: document.getElementById('modalCloseBtn'),
        modalTitle: document.getElementById('modalTitle'),
        modalBreadcrumb: document.getElementById('modalBreadcrumb'),
        modalCopyCodeBtn: document.getElementById('modalCopyCodeBtn'),
        modalDownloadBtn: document.getElementById('modalDownloadBtn'),
        modalGithubLink: document.getElementById('modalGithubLink'),
        modalTabs: document.querySelectorAll('.modal-tab-btn'),
        modalCodePanel: document.getElementById('modalCodePanel'),
        modalAnalysisPanel: document.getElementById('modalAnalysisPanel'),
        modalTerminalPanel: document.getElementById('modalTerminalPanel'),
        modalDocsPanel: document.getElementById('modalDocsPanel'),
        modalReviewPanel: document.getElementById('modalReviewPanel'),
        modalCodeWrapper: document.getElementById('modalCodeWrapper'),
        modalAnalysisContent: document.getElementById('modalAnalysisContent'),
        modalTerminalBody: document.getElementById('modalTerminalBody'),
        modalDocsContent: document.getElementById('modalDocsContent'),
        modalReviewCheck: document.getElementById('modalReviewCheck'),
        modalReviewScore: document.getElementById('modalReviewScore'),
        modalReviewNotes: document.getElementById('modalReviewNotes'),
        
        // Toast
        toastContainer: document.getElementById('toastContainer')
    };

    // =========================================================================
    // INITIALIZATION
    // =========================================================================
    function init() {
        applyTheme(state.theme);
        setupEventListeners();
        renderModulePills();
        renderCurrentView();
        updateReviewProgressMetrics();
    }

    // =========================================================================
    // THEME MANAGEMENT
    // =========================================================================
    function applyTheme(theme) {
        state.theme = theme;
        document.documentElement.setAttribute('data-theme', theme);
        localStorage.setItem('daspro_theme', theme);
        if (elements.themeToggleBtn) {
            elements.themeToggleBtn.innerHTML = theme === 'dark' 
                ? '<svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><circle cx="12" cy="12" r="5"/><line x1="12" y1="1" x2="12" y2="3"/><line x1="12" y1="21" x2="12" y2="23"/><line x1="4.22" y1="4.22" x2="5.64" y2="5.64"/><line x1="18.36" y1="18.36" x2="19.78" y2="19.78"/><line x1="1" y1="12" x2="3" y2="12"/><line x1="21" y1="12" x2="23" y2="12"/><line x1="4.22" y1="19.78" x2="5.64" y2="18.36"/><line x1="18.36" y1="5.64" x2="19.78" y2="4.22"/></svg>'
                : '<svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M21 12.79A9 9 0 1 1 11.21 3 7 7 0 0 0 21 12.79z"/></svg>';
        }
    }

    function toggleTheme() {
        const newTheme = state.theme === 'dark' ? 'light' : 'dark';
        applyTheme(newTheme);
        showToast(`Beralih ke mode ${newTheme === 'dark' ? 'gelap (Dark Mode)' : 'terang (Light Mode)'}`, 'info');
    }

    // =========================================================================
    // NOTIFICATIONS (TOAST)
    // =========================================================================
    function showToast(message, type = 'info') {
        if (!elements.toastContainer) return;
        const toast = document.createElement('div');
        toast.className = `toast ${type}`;
        
        let iconSvg = '';
        if (type === 'success') {
            iconSvg = '<svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="#10b981" stroke-width="2.5"><polyline points="20 6 9 17 4 12"></polyline></svg>';
        } else {
            iconSvg = '<svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="#38bdf8" stroke-width="2"><circle cx="12" cy="12" r="10"></circle><line x1="12" y1="16" x2="12" y2="12"></line><line x1="12" y1="8" x2="12.01" y2="8"></line></svg>';
        }

        toast.innerHTML = `${iconSvg}<span>${message}</span>`;
        elements.toastContainer.appendChild(toast);

        setTimeout(() => toast.classList.add('show'), 10);
        setTimeout(() => {
            toast.classList.remove('show');
            setTimeout(() => toast.remove(), 300);
        }, 3000);
    }

    function copyToClipboard(text, successMsg = 'Teks berhasil disalin!') {
        if (navigator.clipboard && window.isSecureContext) {
            navigator.clipboard.writeText(text).then(() => {
                showToast(successMsg, 'success');
            }).catch(() => fallbackCopy(text, successMsg));
        } else {
            fallbackCopy(text, successMsg);
        }
    }

    function fallbackCopy(text, successMsg) {
        const textArea = document.createElement('textarea');
        textArea.value = text;
        textArea.style.position = 'fixed';
        textArea.style.left = '-999999px';
        document.body.appendChild(textArea);
        textArea.focus();
        textArea.select();
        try {
            document.execCommand('copy');
            showToast(successMsg, 'success');
        } catch (err) {
            showToast('Gagal menyalin teks ke clipboard', 'info');
        }
        textArea.remove();
    }

    // =========================================================================
    // EVENT LISTENERS
    // =========================================================================
    function setupEventListeners() {
        // Theme toggle
        if (elements.themeToggleBtn) {
            elements.themeToggleBtn.addEventListener('click', toggleTheme);
        }

        // Copy NIM
        if (elements.nimCopyBadge) {
            elements.nimCopyBadge.addEventListener('click', () => {
                const nim = state.stats.profile ? state.stats.profile.nim : 'A11.2026.16638';
                copyToClipboard(nim, `NIM ${nim} berhasil disalin!`);
            });
        }

        // Keyboard search shortcut (Ctrl+K or /)
        window.addEventListener('keydown', (e) => {
            if ((e.ctrlKey && e.key === 'k') || (e.key === '/' && document.activeElement.tagName !== 'INPUT' && document.activeElement.tagName !== 'TEXTAREA')) {
                e.preventDefault();
                if (elements.searchInput) {
                    elements.searchInput.focus();
                    elements.searchInput.select();
                }
            }
            if (e.key === 'Escape' && elements.taskModal && elements.taskModal.classList.contains('active')) {
                closeTaskModal();
            }
        });

        // Search trigger in navbar
        if (elements.navSearchTrigger) {
            elements.navSearchTrigger.addEventListener('click', () => {
                switchView('explorer');
                if (elements.searchInput) {
                    elements.searchInput.focus();
                    elements.searchInput.select();
                }
            });
        }

        // Search Input
        if (elements.searchInput) {
            elements.searchInput.addEventListener('input', (e) => {
                state.searchQuery = e.target.value.trim().toLowerCase();
                if (elements.searchClearBtn) {
                    elements.searchClearBtn.style.display = state.searchQuery ? 'block' : 'none';
                }
                renderAssignmentGrid();
            });
        }

        if (elements.searchClearBtn) {
            elements.searchClearBtn.addEventListener('click', () => {
                elements.searchInput.value = '';
                state.searchQuery = '';
                elements.searchClearBtn.style.display = 'none';
                renderAssignmentGrid();
                elements.searchInput.focus();
            });
        }

        // Select Filters
        if (elements.moduleFilterSelect) {
            elements.moduleFilterSelect.addEventListener('change', (e) => {
                state.activeModuleFilter = e.target.value;
                updateActiveModulePill();
                renderAssignmentGrid();
            });
        }

        if (elements.fileTypeSelect) {
            elements.fileTypeSelect.addEventListener('change', (e) => {
                state.activeFileTypeFilter = e.target.value;
                renderAssignmentGrid();
            });
        }

        if (elements.sortSelect) {
            elements.sortSelect.addEventListener('change', (e) => {
                state.sortBy = e.target.value;
                renderAssignmentGrid();
            });
        }

        if (elements.reviewFilterSelect) {
            elements.reviewFilterSelect.addEventListener('change', (e) => {
                state.reviewStatusFilter = e.target.value;
                renderAssignmentGrid();
            });
        }

        // View Tabs Switching
        elements.viewTabs.forEach(btn => {
            btn.addEventListener('click', () => {
                const targetView = btn.getAttribute('data-view');
                switchView(targetView);
            });
        });

        // Review Center Actions
        if (elements.markAllReviewedBtn) {
            elements.markAllReviewedBtn.addEventListener('click', () => {
                state.assignments.forEach(t => {
                    if (!state.reviews[t.id]) state.reviews[t.id] = {};
                    state.reviews[t.id].checked = true;
                    state.reviews[t.id].date = new Date().toLocaleDateString('id-ID');
                });
                saveReviews();
                renderReviewCenter();
                renderAssignmentGrid();
                updateReviewProgressMetrics();
                showToast('Semua 32 tugas telah ditandai sebagai Selesai Diperiksa!', 'success');
            });
        }

        if (elements.resetReviewBtn) {
            elements.resetReviewBtn.addEventListener('click', () => {
                if (confirm('Apakah Anda yakin ingin mereset seluruh checklist review tugas?')) {
                    state.reviews = {};
                    saveReviews();
                    renderReviewCenter();
                    renderAssignmentGrid();
                    updateReviewProgressMetrics();
                    showToast('Checklist review berhasil direset.', 'info');
                }
            });
        }

        if (elements.exportReviewBtn) {
            elements.exportReviewBtn.addEventListener('click', exportReviewReport);
        }

        // Modal Close
        if (elements.modalCloseBtn) {
            elements.modalCloseBtn.addEventListener('click', closeTaskModal);
        }

        if (elements.taskModal) {
            elements.taskModal.addEventListener('click', (e) => {
                if (e.target === elements.taskModal) closeTaskModal();
            });
        }

        // Modal Tabs
        elements.modalTabs.forEach(btn => {
            btn.addEventListener('click', () => {
                const tabName = btn.getAttribute('data-tab');
                switchModalTab(tabName);
            });
        });

        // Modal Action: Copy Code
        if (elements.modalCopyCodeBtn) {
            elements.modalCopyCodeBtn.addEventListener('click', () => {
                if (state.currentOpenTask) {
                    copyToClipboard(state.currentOpenTask.code, `Kode ${state.currentOpenTask.cppName} berhasil disalin!`);
                }
            });
        }

        // Modal Action: Download Code
        if (elements.modalDownloadBtn) {
            elements.modalDownloadBtn.addEventListener('click', () => {
                if (state.currentOpenTask) {
                    downloadFile(state.currentOpenTask.cppName, state.currentOpenTask.code);
                }
            });
        }

        // Modal Review Controls
        if (elements.modalReviewCheck) {
            elements.modalReviewCheck.addEventListener('change', (e) => {
                if (state.currentOpenTask) {
                    setTaskReview(state.currentOpenTask.id, e.target.checked);
                    renderAssignmentGrid();
                    updateReviewProgressMetrics();
                }
            });
        }

        if (elements.modalReviewScore) {
            elements.modalReviewScore.addEventListener('input', (e) => {
                if (state.currentOpenTask) {
                    if (!state.reviews[state.currentOpenTask.id]) state.reviews[state.currentOpenTask.id] = {};
                    state.reviews[state.currentOpenTask.id].score = e.target.value;
                    saveReviews();
                }
            });
        }

        if (elements.modalReviewNotes) {
            elements.modalReviewNotes.addEventListener('input', (e) => {
                if (state.currentOpenTask) {
                    if (!state.reviews[state.currentOpenTask.id]) state.reviews[state.currentOpenTask.id] = {};
                    state.reviews[state.currentOpenTask.id].notes = e.target.value;
                    saveReviews();
                }
            });
        }
    }

    // =========================================================================
    // VIEW SWITCHER
    // =========================================================================
    function switchView(viewName) {
        state.currentView = viewName;
        
        elements.viewTabs.forEach(tab => {
            if (tab.getAttribute('data-view') === viewName) {
                tab.classList.add('active');
            } else {
                tab.classList.remove('active');
            }
        });

        if (elements.viewExplorer) elements.viewExplorer.style.display = viewName === 'explorer' ? 'block' : 'none';
        if (elements.viewReview) elements.viewReview.style.display = viewName === 'review' ? 'block' : 'none';
        if (elements.viewPdf) elements.viewPdf.style.display = viewName === 'pdf' ? 'block' : 'none';
        if (elements.viewAnalytics) elements.viewAnalytics.style.display = viewName === 'analytics' ? 'block' : 'none';

        renderCurrentView();
    }

    function renderCurrentView() {
        if (state.currentView === 'explorer') {
            renderAssignmentGrid();
        } else if (state.currentView === 'review') {
            renderReviewCenter();
        } else if (state.currentView === 'pdf') {
            renderPdfCatalog();
        } else if (state.currentView === 'analytics') {
            renderAnalytics();
        }
    }

    // =========================================================================
    // MODULE PILLS
    // =========================================================================
    function renderModulePills() {
        if (!elements.modulePillsContainer) return;
        
        const modules = state.stats.modules || [];
        let html = `
            <button class="module-pill active" data-mod="all">
                Semua Modul <span class="tab-badge">${state.assignments.length}</span>
            </button>
        `;

        modules.forEach(m => {
            html += `
                <button class="module-pill" data-mod="${m.dirName}">
                    ${m.dirName} <span class="tab-badge">${m.cppCount}</span>
                </button>
            `;
        });

        elements.modulePillsContainer.innerHTML = html;

        elements.modulePillsContainer.querySelectorAll('.module-pill').forEach(btn => {
            btn.addEventListener('click', () => {
                const mod = btn.getAttribute('data-mod');
                state.activeModuleFilter = mod;
                if (elements.moduleFilterSelect) elements.moduleFilterSelect.value = mod;
                updateActiveModulePill();
                renderAssignmentGrid();
            });
        });
    }

    function updateActiveModulePill() {
        if (!elements.modulePillsContainer) return;
        elements.modulePillsContainer.querySelectorAll('.module-pill').forEach(btn => {
            if (btn.getAttribute('data-mod') === state.activeModuleFilter) {
                btn.classList.add('active');
            } else {
                btn.classList.remove('active');
            }
        });
    }

    // =========================================================================
    // VIEW 1: ASSIGNMENT GRID EXPLORER
    // =========================================================================
    function getFilteredAssignments() {
        let list = [...state.assignments];

        // Filter: Module
        if (state.activeModuleFilter !== 'all') {
            list = list.filter(item => item.module === state.activeModuleFilter);
        }

        // Filter: File Type
        if (state.activeFileTypeFilter === 'cpp') {
            list = list.filter(item => item.cppPath);
        } else if (state.activeFileTypeFilter === 'pdf') {
            list = list.filter(item => item.pdf);
        } else if (state.activeFileTypeFilter === 'docx') {
            list = list.filter(item => item.docx);
        }

        // Filter: Review Status
        if (state.reviewStatusFilter === 'reviewed') {
            list = list.filter(item => state.reviews[item.id] && state.reviews[item.id].checked);
        } else if (state.reviewStatusFilter === 'unreviewed') {
            list = list.filter(item => !state.reviews[item.id] || !state.reviews[item.id].checked);
        }

        // Filter: Search Query
        if (state.searchQuery) {
            const q = state.searchQuery;
            list = list.filter(item => {
                return item.title.toLowerCase().includes(q) ||
                    item.topic.toLowerCase().includes(q) ||
                    item.description.toLowerCase().includes(q) ||
                    item.cppName.toLowerCase().includes(q) ||
                    item.caseLabel.toLowerCase().includes(q) ||
                    (item.concepts && item.concepts.some(c => c.toLowerCase().includes(q))) ||
                    item.code.toLowerCase().includes(q);
            });
        }

        // Sort
        if (state.sortBy === 'loc_desc') {
            list.sort((a, b) => b.loc - a.loc);
        } else if (state.sortBy === 'name_asc') {
            list.sort((a, b) => a.title.localeCompare(b.title));
        } else {
            // Default: curriculum order
            list.sort((a, b) => a.counter - b.counter);
        }

        return list;
    }

    function renderAssignmentGrid() {
        if (!elements.assignmentGrid) return;
        const filtered = getFilteredAssignments();

        if (elements.assignmentCountLabel) {
            elements.assignmentCountLabel.textContent = `${filtered.length} Tugas`;
        }

        if (filtered.length === 0) {
            elements.assignmentGrid.innerHTML = `
                <div class="empty-state">
                    <div class="empty-icon">🔍</div>
                    <div class="empty-title">Tidak ada tugas yang sesuai</div>
                    <div class="empty-text">Coba ubah kata kunci pencarian atau sesuaikan opsi filter di atas.</div>
                </div>
            `;
            return;
        }

        let html = '';
        filtered.forEach(task => {
            const isReviewed = state.reviews[task.id] && state.reviews[task.id].checked;
            const subLabel = task.subfolder ? task.subfolder.split('/')[0] : task.module;

            let conceptsHtml = '';
            if (task.concepts && task.concepts.length > 0) {
                conceptsHtml = task.concepts.slice(0, 3).map(c => `
                    <span class="concept-chip" onclick="window.filterByConcept('${c}')">${c}</span>
                `).join('');
            }

            const pdfBtnHtml = task.pdf ? `
                <a href="${task.pdf.path}" target="_blank" class="btn btn-secondary btn-sm" title="Buka Dokumen PDF (${task.pdf.name})">
                    <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="#f43f5e" stroke-width="2"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8z"></path><polyline points="14 2 14 8 20 8"></polyline><line x1="16" y1="13" x2="8" y2="13"></line><line x1="16" y1="17" x2="8" y2="17"></line><polyline points="10 9 9 9 8 9"></polyline></svg>
                    PDF
                </a>
            ` : '';

            html += `
                <div class="task-card ${isReviewed ? 'reviewed' : ''}" id="card-${task.id}">
                    <div>
                        <div class="card-top">
                            <div class="card-badges">
                                <span class="badge-module">${subLabel}</span>
                                <span class="badge-case">${task.caseLabel}</span>
                            </div>
                            <button class="review-check-toggle ${isReviewed ? 'checked' : ''}" 
                                onclick="window.toggleReview('${task.id}', event)"
                                title="${isReviewed ? 'Sudah diperiksa (Klik untuk batal)' : 'Tandai sudah diperiksa'}">
                                <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="3">
                                    <polyline points="20 6 9 17 4 12"></polyline>
                                </svg>
                            </button>
                        </div>
                        <h3 class="card-title">${task.title}</h3>
                        <p class="card-desc">${task.description}</p>
                        <div class="card-concept-tags">
                            ${conceptsHtml}
                        </div>
                    </div>

                    <div>
                        <div class="card-meta-bar">
                            <div class="meta-stats">
                                <span class="meta-stat-item" title="Jumlah Baris Kode">
                                    <svg width="13" height="13" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><polyline points="16 18 22 12 16 6"></polyline><polyline points="8 6 2 12 8 18"></polyline></svg>
                                    ${task.loc} LOC
                                </span>
                                <span class="meta-stat-item" title="Ukuran File C++">
                                    <svg width="13" height="13" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M13 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V9z"></path><polyline points="13 2 13 9 20 9"></polyline></svg>
                                    ${task.cppSize}
                                </span>
                            </div>
                            <span style="color: ${isReviewed ? 'var(--brand-emerald)' : 'var(--text-muted)'}; font-size: 0.72rem; font-weight: 600;">
                                ${isReviewed ? '● Terverifikasi' : '○ Siap Dicek'}
                            </span>
                        </div>

                        <div class="card-actions">
                            <button class="btn btn-primary btn-sm" onclick="window.openTaskDetail('${task.id}')">
                                <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><polygon points="5 3 19 12 5 21 5 3"></polygon></svg>
                                Buka Kode & Detail
                            </button>
                            <button class="btn btn-secondary btn-sm" onclick="window.copyTaskCode('${task.id}', event)" title="Salin Kode C++">
                                <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><rect x="9" y="9" width="13" height="13" rx="2" ry="2"></rect><path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"></path></svg>
                            </button>
                            ${pdfBtnHtml}
                        </div>
                    </div>
                </div>
            `;
        });

        elements.assignmentGrid.innerHTML = html;
    }

    // Global helper for concept click
    window.filterByConcept = function (concept) {
        if (elements.searchInput) {
            elements.searchInput.value = concept;
            state.searchQuery = concept.toLowerCase();
            if (elements.searchClearBtn) elements.searchClearBtn.style.display = 'block';
            renderAssignmentGrid();
            window.scrollTo({ top: 350, behavior: 'smooth' });
        }
    };

    // =========================================================================
    // VIEW 2: CEK TUGAS & REVIEW CENTER
    // =========================================================================
    function renderReviewCenter() {
        if (!elements.reviewTableBody) return;

        let html = '';
        state.assignments.forEach((task, idx) => {
            const rev = state.reviews[task.id] || {};
            const isChecked = Boolean(rev.checked);
            const scoreVal = rev.score || '100';
            const notesVal = rev.notes || '';

            html += `
                <tr class="${isChecked ? 'row-checked' : ''}" id="rev-row-${task.id}">
                    <td style="font-family: var(--font-mono); color: var(--text-muted); font-size: 0.78rem;">
                        ${(idx + 1).toString().padStart(2, '0')}
                    </td>
                    <td>
                        <div style="font-weight: 700; color: var(--text-primary);">${task.title}</div>
                        <div style="font-size: 0.75rem; color: var(--text-muted); font-family: var(--font-mono);">${task.cppName}</div>
                    </td>
                    <td>
                        <span class="badge-module" style="font-size: 0.68rem;">${task.module}</span>
                    </td>
                    <td style="font-family: var(--font-mono); font-size: 0.8rem; color: var(--text-secondary);">
                        ${task.loc} LOC
                    </td>
                    <td>
                        <label style="display: flex; align-items: center; gap: 0.5rem; cursor: pointer;">
                            <input type="checkbox" style="width: 17px; height: 17px; accent-color: var(--brand-emerald);"
                                ${isChecked ? 'checked' : ''}
                                onchange="window.handleTableCheckChange('${task.id}', this.checked)">
                            <span style="font-size: 0.78rem; font-weight: 600; color: ${isChecked ? 'var(--brand-emerald)' : 'var(--text-muted)'};">
                                ${isChecked ? 'Sudah Diperiksa' : 'Belum'}
                            </span>
                        </label>
                    </td>
                    <td>
                        <input type="text" class="score-input" value="${scoreVal}" placeholder="100"
                            onchange="window.handleTableScoreChange('${task.id}', this.value)">
                    </td>
                    <td>
                        <input type="text" class="review-notes-input" value="${notesVal}" placeholder="Catatan evaluasi / feedback..."
                            onchange="window.handleTableNotesChange('${task.id}', this.value)">
                    </td>
                    <td>
                        <div style="display: flex; gap: 0.35rem;">
                            <button class="btn btn-secondary btn-sm" onclick="window.openTaskDetail('${task.id}')" title="Buka Detail">
                                Detail
                            </button>
                            ${task.pdf ? `
                                <a href="${task.pdf.path}" target="_blank" class="btn btn-ghost btn-sm" title="PDF">
                                    📄
                                </a>
                            ` : ''}
                        </div>
                    </td>
                </tr>
            `;
        });

        elements.reviewTableBody.innerHTML = html;
        updateReviewProgressMetrics();
    }

    function updateReviewProgressMetrics() {
        const total = state.assignments.length;
        const reviewedCount = state.assignments.filter(t => state.reviews[t.id] && state.reviews[t.id].checked).length;
        const pct = total > 0 ? Math.round((reviewedCount / total) * 100) : 0;

        if (elements.reviewProgressBarFill) {
            elements.reviewProgressBarFill.style.width = `${pct}%`;
        }
        if (elements.reviewProgressPctLabel) {
            elements.reviewProgressPctLabel.textContent = `${pct}%`;
        }
        if (elements.reviewProgressCountLabel) {
            elements.reviewProgressCountLabel.textContent = `${reviewedCount} / ${total} Tugas Terverifikasi`;
        }
    }

    function saveReviews() {
        localStorage.setItem('daspro_reviews_A11_2026_16638', JSON.stringify(state.reviews));
    }

    function setTaskReview(taskId, isChecked) {
        if (!state.reviews[taskId]) state.reviews[taskId] = {};
        state.reviews[taskId].checked = isChecked;
        if (isChecked && !state.reviews[taskId].date) {
            state.reviews[taskId].date = new Date().toLocaleDateString('id-ID');
        }
        saveReviews();
    }

    window.toggleReview = function (taskId, e) {
        if (e) e.stopPropagation();
        const current = state.reviews[taskId] && state.reviews[taskId].checked;
        const nextState = !current;
        setTaskReview(taskId, nextState);
        renderAssignmentGrid();
        updateReviewProgressMetrics();
        showToast(nextState ? 'Tugas ditandai: Sudah Diperiksa ✅' : 'Tugas dikembalikan: Belum Diperiksa', nextState ? 'success' : 'info');
    };

    window.handleTableCheckChange = function (taskId, checked) {
        setTaskReview(taskId, checked);
        const row = document.getElementById(`rev-row-${taskId}`);
        if (row) {
            if (checked) row.classList.add('row-checked');
            else row.classList.remove('row-checked');
        }
        updateReviewProgressMetrics();
        showToast(checked ? 'Status disimpan: Diperiksa ✅' : 'Status diperbarui', checked ? 'success' : 'info');
    };

    window.handleTableScoreChange = function (taskId, score) {
        if (!state.reviews[taskId]) state.reviews[taskId] = {};
        state.reviews[taskId].score = score;
        saveReviews();
    };

    window.handleTableNotesChange = function (taskId, notes) {
        if (!state.reviews[taskId]) state.reviews[taskId] = {};
        state.reviews[taskId].notes = notes;
        saveReviews();
    };

    function exportReviewReport() {
        const total = state.assignments.length;
        const reviewedCount = state.assignments.filter(t => state.reviews[t.id] && state.reviews[t.id].checked).length;
        const pct = total > 0 ? Math.round((reviewedCount / total) * 100) : 0;
        const profile = state.stats.profile || {};

        let report = `========================================================================\n`;
        report += `    REKAPITULASI PENILAIAN & VERIFIKASI TUGAS DASPRO UDINUS            \n`;
        report += `========================================================================\n`;
        report += `Nama Mahasiswa : ${profile.name || 'Muhammad Fajri Setyawan'}\n`;
        report += `NIM            : ${profile.nim || 'A11.2026.16638'}\n`;
        report += `Program Studi  : ${profile.prodi || 'Teknik Informatika'}\n`;
        report += `Institusi      : ${profile.univ || 'Universitas Dian Nuswantoro (UDINUS)'}\n`;
        report += `Mata Kuliah    : ${profile.course || 'Dasar Pemrograman (DASPRO)'}\n`;
        report += `Tanggal Cek    : ${new Date().toLocaleDateString('id-ID', { dateStyle: 'full' })}\n`;
        report += `Status Review  : ${reviewedCount}/${total} Tugas Selesai Diperiksa (${pct}%)\n`;
        report += `========================================================================\n\n`;

        state.assignments.forEach((t, i) => {
            const rev = state.reviews[t.id] || {};
            const checkedStr = rev.checked ? '[SUDAH DIPERIKSA]' : '[BELUM DIPERIKSA]';
            const scoreStr = rev.score ? `Skor: ${rev.score}/100` : 'Skor: 100/100';
            const notesStr = rev.notes ? `Catatan: ${rev.notes}` : 'Catatan: Program valid & sesuai spesifikasi.';

            report += `${(i + 1).toString().padStart(2, '0')}. ${t.title} (${t.module})\n`;
            report += `    Berkas : ${t.cppName} (${t.loc} LOC)\n`;
            report += `    Status : ${checkedStr} | ${scoreStr}\n`;
            report += `    ${notesStr}\n\n`;
        });

        report += `========================================================================\n`;
        report += `Dihasilkan otomatis oleh DASPRO Assignment Explorer Hub\n`;
        report += `Repositori: https://github.com/LazenFajri/daspro_A11.2026.16638\n`;

        copyToClipboard(report, 'Laporan rekap review tugas berhasil disalin ke clipboard!');
    }

    // =========================================================================
    // VIEW 3: PDF DOCUMENT HUB
    // =========================================================================
    function renderPdfCatalog() {
        if (!elements.pdfGrid) return;
        const pdfs = state.pdfs || [];

        if (pdfs.length === 0) {
            elements.pdfGrid.innerHTML = `
                <div class="empty-state">
                    <div class="empty-icon">📑</div>
                    <div class="empty-title">Tidak ada dokumen PDF terdeteksi</div>
                </div>
            `;
            return;
        }

        let html = '';
        pdfs.forEach(doc => {
            html += `
                <div class="pdf-card">
                    <div>
                        <div class="pdf-header">
                            <div class="pdf-icon">
                                <svg width="22" height="22" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                    <path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8z"></path>
                                    <polyline points="14 2 14 8 20 8"></polyline>
                                </svg>
                            </div>
                            <div class="pdf-info-wrap">
                                <div class="pdf-filename" title="${doc.name}">${doc.name}</div>
                                <div class="pdf-module-badge">${doc.module} • <span style="font-family: var(--font-mono);">${doc.size}</span></div>
                            </div>
                        </div>
                        <div style="font-size: 0.78rem; color: var(--text-secondary); margin-bottom: 1rem;">
                            Kategori: <span class="badge-tag">${doc.docType}</span>
                        </div>
                    </div>
                    <div style="display: flex; gap: 0.5rem;">
                        <a href="${doc.path}" target="_blank" class="btn btn-primary btn-sm" style="flex: 1;">
                            <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M1 12s4-8 11-8 11 8 11 8-4 8-11 8-11-8-11-8z"></path><circle cx="12" cy="12" r="3"></circle></svg>
                            Buka PDF
                        </a>
                        <a href="${doc.path}" download class="btn btn-secondary btn-sm" title="Unduh File PDF">
                            <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4"></path><polyline points="7 10 12 15 17 10"></polyline><line x1="12" y1="15" x2="12" y2="3"></line></svg>
                        </a>
                    </div>
                </div>
            `;
        });

        elements.pdfGrid.innerHTML = html;
    }

    // =========================================================================
    // VIEW 4: ANALYTICS & INSIGHTS
    // =========================================================================
    function renderAnalytics() {
        if (!elements.moduleAnalyticsContainer || !elements.conceptCloudContainer) return;
        const modules = state.stats.modules || [];

        // Module breakdown cards
        let modHtml = '';
        modules.forEach(m => {
            modHtml += `
                <div class="module-overview-card">
                    <div>
                        <h4 class="module-card-title">${m.title}</h4>
                        <p class="module-card-topic">${m.topic}</p>
                    </div>
                    <div class="module-stats-list">
                        <div>
                            <div class="module-stat-val">${m.cppCount}</div>
                            <div class="module-stat-lbl">File C++</div>
                        </div>
                        <div>
                            <div class="module-stat-val">${m.pdfCount}</div>
                            <div class="module-stat-lbl">Dokumen PDF</div>
                        </div>
                        <div>
                            <div class="module-stat-val">${m.loc}</div>
                            <div class="module-stat-lbl">Total LOC</div>
                        </div>
                    </div>
                </div>
            `;
        });
        elements.moduleAnalyticsContainer.innerHTML = modHtml;

        // Concept tag aggregation
        const conceptCounts = {};
        state.assignments.forEach(t => {
            if (t.concepts) {
                t.concepts.forEach(c => {
                    conceptCounts[c] = (conceptCounts[c] || 0) + 1;
                });
            }
        });

        const sortedConcepts = Object.entries(conceptCounts).sort((a, b) => b[1] - a[1]);
        let cloudHtml = '<div style="display: flex; flex-wrap: wrap; gap: 0.6rem;">';
        sortedConcepts.forEach(([name, count]) => {
            cloudHtml += `
                <button class="btn btn-secondary btn-sm" onclick="window.filterByConcept('${name}'); window.switchView('explorer');" style="border-radius: var(--radius-full);">
                    <span>${name}</span>
                    <span class="tab-badge" style="background: var(--brand-indigo); color: white;">${count}</span>
                </button>
            `;
        });
        cloudHtml += '</div>';
        elements.conceptCloudContainer.innerHTML = cloudHtml;
    }

    // =========================================================================
    // MODAL DRAWER (CODE VIEWER & SOLUTION DETAILS)
    // =========================================================================
    window.openTaskDetail = function (taskId, initialTab = 'code') {
        const task = state.assignments.find(t => t.id === taskId);
        if (!task || !elements.taskModal) return;

        state.currentOpenTask = task;

        // Set Headers
        if (elements.modalTitle) elements.modalTitle.textContent = task.title;
        if (elements.modalBreadcrumb) {
            elements.modalBreadcrumb.innerHTML = `
                <span>${task.module}</span> / 
                <span>${task.subfolder || 'Utama'}</span> / 
                <span style="color: var(--text-primary); font-weight: 600;">${task.cppName}</span>
            `;
        }

        if (elements.modalGithubLink) {
            elements.modalGithubLink.href = task.githubBlob;
        }

        // Render Code with Prism
        if (elements.modalCodeWrapper) {
            if (typeof window.renderHighlightedCpp === 'function') {
                elements.modalCodeWrapper.innerHTML = window.renderHighlightedCpp(task.code);
            } else {
                elements.modalCodeWrapper.innerHTML = `<pre class="line-code"><code>${escapeHtml(task.code)}</code></pre>`;
            }
        }

        // Render Analysis & Concepts
        if (elements.modalAnalysisContent) {
            const conceptsBadges = task.concepts.map(c => `<span class="concept-chip">${c}</span>`).join(' ');
            elements.modalAnalysisContent.innerHTML = `
                <div class="analysis-card">
                    <div class="analysis-title">
                        <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="#38bdf8" stroke-width="2"><circle cx="12" cy="12" r="10"></circle><line x1="12" y1="16" x2="12" y2="12"></line><line x1="12" y1="8" x2="12.01" y2="8"></line></svg>
                        Ringkasan Kasus & Masalah
                    </div>
                    <div class="analysis-content">
                        <p style="margin-bottom: 0.85rem;">${task.description}</p>
                        <div style="display: flex; gap: 0.4rem; align-items: center; flex-wrap: wrap;">
                            <strong style="font-size: 0.78rem; color: var(--text-primary);">Konsep Pemrograman:</strong>
                            ${conceptsBadges}
                        </div>
                    </div>
                </div>

                <div class="analysis-card">
                    <div class="analysis-title">
                        <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="#10b981" stroke-width="2"><path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8z"></path><polyline points="14 2 14 8 20 8"></polyline><line x1="16" y1="13" x2="8" y2="13"></line><line x1="16" y1="17" x2="8" y2="17"></line><polyline points="10 9 9 9 8 9"></polyline></svg>
                        Analisis Algoritma & Logika Pemrograman
                    </div>
                    <div class="analysis-content">
                        <p style="margin-bottom: 1rem;">${task.analysis}</p>
                        
                        <div style="background: rgba(255,255,255,0.03); border: 1px solid var(--border-subtle); border-radius: var(--radius-md); padding: 1rem;">
                            <div style="font-weight: 700; color: var(--text-primary); margin-bottom: 0.5rem; font-size: 0.82rem;">Spesifikasi Berkas:</div>
                            <ul style="padding-left: 1.25rem; font-size: 0.8rem; color: var(--text-secondary); line-height: 1.8;">
                                <li>Nama Berkas Sumber: <code style="font-family: var(--font-mono); color: #38bdf8;">${task.cppName}</code></li>
                                <li>Standar Kompiler: <code style="font-family: var(--font-mono);">C++17 (ISO/IEC 14882:2017)</code></li>
                                <li>Jumlah Baris Kode (LOC): <code style="font-family: var(--font-mono); color: #10b981;">${task.loc} baris</code></li>
                                <li>Ukuran File: <code style="font-family: var(--font-mono);">${task.cppSize}</code></li>
                            </ul>
                        </div>
                    </div>
                </div>
            `;
        }

        // Render Terminal Simulation
        if (elements.modalTerminalBody) {
            elements.modalTerminalBody.textContent = task.simulatedTerminal || `$ g++ -std=c++17 "${task.cppName}" -o app && ./app\n>> Program dieksekusi dengan normal.`;
        }

        // Render Docs Tab
        if (elements.modalDocsContent) {
            let docsHtml = '';
            if (task.pdf) {
                docsHtml += `
                    <div class="analysis-card">
                        <div class="analysis-title">
                            <span style="font-size: 1.25rem;">📄</span>
                            Dokumen Laporan / Notasi Algoritmik Terkait
                        </div>
                        <div class="analysis-content">
                            <p style="margin-bottom: 1rem;">Dokumen analisis pendukung untuk kasus ini telah diverifikasi dan siap dibaca:</p>
                            <div style="display: flex; align-items: center; justify-content: space-between; background: rgba(255,255,255,0.03); padding: 1rem; border-radius: var(--radius-md); border: 1px solid var(--border-subtle);">
                                <div>
                                    <div style="font-weight: 700; color: var(--text-primary);">${task.pdf.name}</div>
                                    <div style="font-size: 0.75rem; color: var(--text-muted); font-family: var(--font-mono);">Ukuran Dokumen: ${task.pdf.size}</div>
                                </div>
                                <div style="display: flex; gap: 0.5rem;">
                                    <a href="${task.pdf.path}" target="_blank" class="btn btn-primary btn-sm">Buka PDF</a>
                                    <a href="${task.pdf.path}" download class="btn btn-secondary btn-sm">Unduh</a>
                                </div>
                            </div>
                        </div>
                    </div>
                `;
            } else {
                docsHtml += `
                    <div class="empty-state" style="padding: 2.5rem 1rem;">
                        <div class="empty-icon">📄</div>
                        <div class="empty-title">Tidak Ada Dokumen PDF Khusus untuk Kasus Ini</div>
                        <div class="empty-text">Implementasi kode mandiri langsung pada berkas C++ (<code style="font-family: var(--font-mono);">${task.cppName}</code>).</div>
                    </div>
                `;
            }

            if (task.docx) {
                docsHtml += `
                    <div class="analysis-card" style="margin-top: 1rem;">
                        <div class="analysis-title">
                            <span style="font-size: 1.25rem;">📝</span>
                            Berkas Panduan Modul (DOCX)
                        </div>
                        <div class="analysis-content">
                            <div style="display: flex; align-items: center; justify-content: space-between;">
                                <div>
                                    <div style="font-weight: 700; color: var(--text-primary);">${task.docx.name}</div>
                                    <div style="font-size: 0.75rem; color: var(--text-muted); font-family: var(--font-mono);">Ukuran: ${task.docx.size}</div>
                                </div>
                                <a href="${task.docx.path}" download class="btn btn-secondary btn-sm">Unduh DOCX</a>
                            </div>
                        </div>
                    </div>
                `;
            }

            elements.modalDocsContent.innerHTML = docsHtml;
        }

        // Render Review Panel Tab
        const rev = state.reviews[task.id] || {};
        if (elements.modalReviewCheck) elements.modalReviewCheck.checked = Boolean(rev.checked);
        if (elements.modalReviewScore) elements.modalReviewScore.value = rev.score || '100';
        if (elements.modalReviewNotes) elements.modalReviewNotes.value = rev.notes || '';

        // Switch to initial tab
        switchModalTab(initialTab);

        // Show Modal
        elements.taskModal.classList.add('active');
        document.body.style.overflow = 'hidden';
    };

    function closeTaskModal() {
        if (!elements.taskModal) return;
        elements.taskModal.classList.remove('active');
        document.body.style.overflow = '';
        state.currentOpenTask = null;
    }

    function switchModalTab(tabName) {
        state.activeModalTab = tabName;
        elements.modalTabs.forEach(btn => {
            if (btn.getAttribute('data-tab') === tabName) {
                btn.classList.add('active');
            } else {
                btn.classList.remove('active');
            }
        });

        if (elements.modalCodePanel) elements.modalCodePanel.classList.toggle('active', tabName === 'code');
        if (elements.modalAnalysisPanel) elements.modalAnalysisPanel.classList.toggle('active', tabName === 'analysis');
        if (elements.modalTerminalPanel) elements.modalTerminalPanel.classList.toggle('active', tabName === 'terminal');
        if (elements.modalDocsPanel) elements.modalDocsPanel.classList.toggle('active', tabName === 'docs');
        if (elements.modalReviewPanel) elements.modalReviewPanel.classList.toggle('active', tabName === 'review');
    }

    // Helper: copy specific task code from card
    window.copyTaskCode = function (taskId, e) {
        if (e) e.stopPropagation();
        const task = state.assignments.find(t => t.id === taskId);
        if (task) {
            copyToClipboard(task.code, `Kode ${task.cppName} berhasil disalin!`);
        }
    };

    // Helper: download file
    function downloadFile(filename, content) {
        const blob = new Blob([content], { type: 'text/plain;charset=utf-8' });
        const url = URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = filename;
        document.body.appendChild(a);
        a.click();
        a.remove();
        URL.revokeObjectURL(url);
        showToast(`Mengunduh file: ${filename}`, 'info');
    }

    function escapeHtml(text) {
        return text
            .replace(/&/g, '&amp;')
            .replace(/</g, '&lt;')
            .replace(/>/g, '&gt;')
            .replace(/"/g, '&quot;')
            .replace(/'/g, '&#039;');
    }

    // Global exposes
    window.switchView = switchView;
    window.DASPRO_APP = {
        state,
        switchView,
        toggleTheme,
        copyToClipboard,
        exportReviewReport
    };

    // Run when DOM ready
    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', init);
    } else {
        init();
    }
})();
