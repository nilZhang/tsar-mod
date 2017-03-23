
/*
 * (C) 2010-2011 Alibaba Group Holding Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#include "tsar.h"

#define STATS_TEST_SIZE (sizeof(struct stats_php_fpm))

static const char *php_fpm_usage = "    --php_fpm               php_fpm information";

/*
 * temp structure for collection infomation.
 */
struct stats_php_fpm {
    unsigned long long    value_1;
    unsigned long long    value_2;
    unsigned long long    value_3;
};

/* Structure for tsar */
static struct mod_info php_fpm_info[] = {
    {"value1", SUMMARY_BIT,  0,  STATS_NULL},
    {"value2", DETAIL_BIT,  0,  STATS_NULL},
    {"value3", DETAIL_BIT,  0,  STATS_NULL}
};

static void
read_php_fpm_stats(struct module *mod, const char *parameter)
{
    /* parameter actually equals to mod->parameter */
    char               buf[256];
    struct stats_php_fpm  st_php_fpm;

    memset(buf, 0, sizeof(buf));
    memset(&st_php_fpm, 0, sizeof(struct stats_php_fpm));

    st_php_fpm.value_1 = 1;
    st_php_fpm.value_2 = 1;
    st_php_fpm.value_3 = 1;

    int pos = sprintf(buf, "%llu,%llu,%llu",
            /* the store order is not same as read procedure */
            st_php_fpm.value_1,
            st_php_fpm.value_2,
            st_php_fpm.value_3);

    buf[pos] = '\0';
    /* send data to tsar you can get it by pre_array&cur_array at set_php_fpm_record */
    set_mod_record(mod, buf);
    return;
}

static void
set_php_fpm_record(struct module *mod, double st_array[],
    U_64 pre_array[], U_64 cur_array[], int inter)
{
    int i;
    /* set st record */
    for (i = 0; i < mod->n_col; i++) {
        st_array[i] = cur_array[i];
    }
}

/* register mod to tsar */
void
mod_register(struct module *mod)
{
    register_mod_fields(mod, "--php_fpm", php_fpm_usage, php_fpm_info, 3, read_php_fpm_stats, set_php_fpm_record);
}
