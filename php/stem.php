#!/usr/bin/php
<?php

namespace Diskerror;

$t = file_get_contents('../text/voc2.txt');

// fwrite(STDOUT, stem($t) . "\n");

fwrite(STDOUT, print_r(stem($t, DISKERROR_STEM_RETURN_ARRAY), true));

// fwrite(STDOUT, stem($t, DISKERROR_STEM_RETURN_BIGRAM) . "\n");

// fwrite(STDOUT, print_r(stem($t, DISKERROR_STEM_RETURN_ARRAY|DISKERROR_STEM_RETURN_BIGRAM), true));

