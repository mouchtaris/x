let SessionLoad = 1
nmap <C-B> :wa<CR>:make clean<CR>:make -j 4<CR>
nmap <C-X> :wa<CR>:make -j 4<CR>
nmap <C-F> :YcmCompleter FixIt<CR>
nmap <C-M> :wa<CR>:bundle exec ruby build.2.rb<CR>
nmap <C-S> :wa<CR>:bundle exec pry -r ./rb/configuration_manager<CR>
