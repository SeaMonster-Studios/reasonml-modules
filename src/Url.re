open Webapi.Url;

type location = {
  .
  "href": string,
  "search": string,
};
[@bs.val] external location: location = "location";

type historyState = {.};

type history = {
  .
  "back": unit => unit,
  "forward": unit => unit,
  "go": int => unit,
  "length": int,
  "state": historyState,
  [@bs.meth]
  "pushState":
    (Js.Nullable.t(historyState), Js.Nullable.t(string), string) => unit,
  [@bs.meth]
  "replaceState":
    (Js.Nullable.t(historyState), Js.Nullable.t(string), string) => unit,
};

[@bs.val] [@bs.scope "window"] external history: history = "history";

let url = make(location##href);
let searchParams = URLSearchParams.make(location##search);

let setUriSearch = search =>
  history##replaceState(
    Js.Nullable.null,
    Js.Nullable.null,
    url->origin ++ url->pathname ++ "?" ++ search,
  );

let paramsArraySeparator = ",";

type paramValues =
  | None
  | Single(string)
  | Multiple(array(string));

let setParamItem = (name: string, value: paramValues): unit =>
  switch (value) {
  | None => ()
  | Single(s) =>
    URLSearchParams.set(name, s, searchParams);
    setUriSearch(URLSearchParams.toString(searchParams));
  | Multiple(m) =>
    URLSearchParams.set(
      name,
      Js.Array.joinWith(paramsArraySeparator, m),
      searchParams,
    );
    setUriSearch(URLSearchParams.toString(searchParams));
  };

let getPramItem = (name: string): paramValues =>
  switch (searchParams |> URLSearchParams.get(name)) {
  | Some(name) =>
    let splitResults = Js.String.split(paramsArraySeparator, name);
    splitResults |> Array.length > 1
      ? splitResults[0] == "" ? None : Multiple(splitResults)
      : name == "" ? None : Single(name);
  | None => None
  };