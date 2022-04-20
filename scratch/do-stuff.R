withr::with_dir(
  "raw_lex/celex_raw/english/emw/",
  {
    shell("awk -f awk/type2fea.awk emw.cd LexField > emw_full.cd")
    data <- readr::read_delim(
      "emw_full.cd",
      delim = "\\",
      col_names = c(
        "rowid",
        "word",
        "sing",
        "plu",
        "pos",
        "comp",
        "sup",
        "inf",
        "part",
        "pres",
        "past",
        "sin1",
        "sin2",
        "sin3",
        "rare"
      )
    )
  }
)

library(tidyverse)
data |>
  mutate(
    across(sing:past, function(x) x == "Y")
  ) |>
  write_csv("scratch/emw.csv")

setwd("raw_lex/celex_raw/english/emw/")
wordforms <- read_delim(
  "emw.cd",
  delim = "\\",
  col_names = c(
    "id_num", "word", "cob",
    "id_num_lemma", "flect_type", "trans_infl"
  ),
  col_types = cols(
    id_num = col_double(),
    word = col_character(),
    cob = col_double(),
    id_num_lemma = col_double(),
    flect_type = col_character(),
    trans_infl = col_character()
  )
)
setwd(here::here())
setwd("raw_lex/celex_raw/english/eml/")

library(tidyverse)
e <- read_csv("emw.csv")



wordforms

lemmas <- read_lines("eml.cd")

head(lemmas)

parse_lemma_line <- function(l) {
  lines <- lemmas |>
    str_split("\\\\")

  tbls <- split(lemmas, lengths(lines)) |>
    lapply(paste0, collapse = "\n") |>
    lapply(read_delim, delim = "\\")
}

problems()


  col_names = c(
    "id_num", "word", "cob",
    "id_num_lemma", "flect_type", "trans_infl"
  ),
  col_types = cols(
    id_num = col_double(),
    word = col_character(),
    cob = col_double(),
    id_num_lemma = col_double(),
    flect_type = col_character(),
    trans_infl = col_character()
  )
)

lemmas |> filter(id_num_lemma == id_num)
tail(lemmas)
