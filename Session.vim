let SessionLoad = 1
nmap <C-B> :wa<CR>:make clean<CR>:make -j 4<CR>
nmap <C-X> :wa<CR>:make -j 4<CR>
nmap <C-F> :YcmCompleter FixIt<CR>
